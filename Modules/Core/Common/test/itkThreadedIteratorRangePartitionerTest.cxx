/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkDomainThreader.h"
#include "itkThreadedIteratorRangePartitioner.h"

namespace
{
class IteratorRangeDomainThreaderAssociate
{
public:
  using Self = IteratorRangeDomainThreaderAssociate;

  using DomainContainerType = std::vector<int>;
  using ThreadedPartitionerType = itk::ThreadedIteratorRangePartitioner<DomainContainerType::const_iterator>;

  class TestDomainThreader : public itk::DomainThreader<ThreadedPartitionerType, Self>
  {
  public:
    ITK_DISALLOW_COPY_AND_MOVE(TestDomainThreader);

    using Self = TestDomainThreader;
    using Superclass = itk::DomainThreader<ThreadedPartitionerType, Self>;
    using Pointer = itk::SmartPointer<Self>;
    using ConstPointer = itk::SmartPointer<const Self>;

    using DomainPartitionerType = Superclass::DomainPartitionerType;
    using DomainType = Superclass::DomainType;

    itkSimpleNewMacro(Self);

    using BorderValuesType = std::vector<int>;
    using DomainBorderValuesInThreadedExecutionType = std::vector<BorderValuesType>;

    const DomainBorderValuesInThreadedExecutionType &
    GetDomainInThreadedExecution() const
    {
      return m_DomainInThreadedExecution;
    }

  protected:
    TestDomainThreader() = default;

  private:
    void
    BeforeThreadedExecution() override
    {
      this->m_DomainInThreadedExecution.resize(this->GetNumberOfWorkUnitsUsed());
      const BorderValuesType unsetBorderValues(2, -1);
      for (auto & i : m_DomainInThreadedExecution)
      {
        i = unsetBorderValues;
      }
    }

    void
    ThreadedExecution(const DomainType & subdomain, const itk::ThreadIdType threadId) override
    {
      if (threadId == 0)
      {
        std::cout << "This is the : " << this->m_Associate->m_ClassDescriptor;
      }
      this->m_DomainInThreadedExecution[threadId].resize(2);
      this->m_DomainInThreadedExecution[threadId][0] = *(subdomain.Begin());
      DomainType::IteratorType it = subdomain.End();
      --it;
      this->m_DomainInThreadedExecution[threadId][1] = *it;
    }

    void
    AfterThreadedExecution() override
    {
      std::cout << "\nDomain partition per thread:" << std::endl;
      for (itk::ThreadIdType i = 0; i < m_DomainInThreadedExecution.size(); ++i)
      {
        std::cout << "ThreadId: " << i << '\t' << m_DomainInThreadedExecution[i][0] << ' '
                  << m_DomainInThreadedExecution[i][1] << std::endl;
      }
      std::cout << std::endl;
    }

    DomainBorderValuesInThreadedExecutionType m_DomainInThreadedExecution;
  }; // end TestDomainThreader class

  IteratorRangeDomainThreaderAssociate()
    : m_ClassDescriptor("enclosing class")
  {
    m_TestDomainThreader = TestDomainThreader::New();
  }

  TestDomainThreader *
  GetDomainThreader()
  {
    return m_TestDomainThreader.GetPointer();
  }

  void
  Execute(const TestDomainThreader::DomainType & completeDomain)
  {
    m_TestDomainThreader->Execute(this, completeDomain);
  }

private:
  TestDomainThreader::Pointer m_TestDomainThreader;

  std::string m_ClassDescriptor;
};


int
ThreadedIteratorRangePartitionerRunTest(
  IteratorRangeDomainThreaderAssociate &                                       enclosingClass,
  itk::ThreadIdType                                                            numberOfThreads,
  const IteratorRangeDomainThreaderAssociate::TestDomainThreader::DomainType & fullDomain)
{
  std::cout << "Testing with " << numberOfThreads << " threads." << std::endl;

  const IteratorRangeDomainThreaderAssociate::TestDomainThreader::Pointer domainThreader =
    enclosingClass.GetDomainThreader();

  // Exercise GetMultiThreader().
  domainThreader->GetMultiThreader();
  domainThreader->SetMaximumNumberOfThreads(numberOfThreads);
  // Possible if numberOfThreads > GlobalMaximumNumberOfThreads
  if (domainThreader->GetMaximumNumberOfThreads() < numberOfThreads)
  {
    std::cerr << "Failed setting requested number of threads: " << numberOfThreads << std::endl
              << "domainThreader->GetMaximumNumberOfThreads(): " << domainThreader->GetMaximumNumberOfThreads()
              << std::endl;
    return EXIT_FAILURE;
  }

  domainThreader->SetNumberOfWorkUnits(numberOfThreads);
  // Possible if numberOfThreads > GlobalMaximumNumberOfThreads
  if (domainThreader->GetNumberOfWorkUnits() != numberOfThreads)
  {
    std::cerr << "Failed setting requested number of work units: " << numberOfThreads << std::endl
              << "domainThreader->GetNumberOfWorkUnits(): " << domainThreader->GetNumberOfWorkUnits() << std::endl;
    return EXIT_FAILURE;
  }

  enclosingClass.Execute(fullDomain);

  /* Did we use as many threads as requested? */
  std::cout << "Requested numberOfThreads: " << numberOfThreads << std::endl
            << "actual: threader->GetNumberOfWorkUnitsUsed(): " << domainThreader->GetNumberOfWorkUnitsUsed() << "\n\n"
            << std::endl;

  /* Check the results. */
  using BorderValuesType = IteratorRangeDomainThreaderAssociate::TestDomainThreader::BorderValuesType;
  int previousEndIndex = -1;
  const IteratorRangeDomainThreaderAssociate::TestDomainThreader::DomainBorderValuesInThreadedExecutionType
    domainInThreadedExecution = domainThreader->GetDomainInThreadedExecution();
  for (itk::ThreadIdType i = 0; i < domainThreader->GetNumberOfWorkUnitsUsed(); ++i)
  {
    BorderValuesType subRange = domainInThreadedExecution[i];
    /* Check that the sub range was assigned something at all */
    if (subRange[0] == -1 || subRange[1] == -1)
    {
      std::cerr << "Error: subRange " << i << " is was not set: " << subRange[i];
      return EXIT_FAILURE;
    }
    /* Check that we got the begin of the range */
    if (i == 0 && subRange[0] != *(fullDomain.Begin()))
    {
      std::cerr << "Error: subRange[0][0] should be " << *(fullDomain.Begin()) << ", but it's " << subRange[0] << '.';
      return EXIT_FAILURE;
    }
    /* Check that we got the end of the range */
    BorderValuesType::const_iterator fullIt = fullDomain.End();
    --fullIt;
    if (i == numberOfThreads - 1 && subRange[1] != *fullIt)
    {
      std::cerr << "Error: subRange[N-1][1] should be " << *fullIt << ", but it's " << subRange[1] << '.';
      return EXIT_FAILURE;
    }
    /* Check that the sub-range endings and beginnings are continuous */
    if (i > 0)
    {
      if (previousEndIndex + 1 != subRange[0])
      {
        std::cerr << "Error: subRange " << i << " is not continuous with "
                  << "previous subRange." << std::endl
                  << "previousEndIndex: " << previousEndIndex << std::endl
                  << "subRange[0]: " << subRange[0] << std::endl;
        return EXIT_FAILURE;
      }
    }
    previousEndIndex = subRange[1];
  }

  return EXIT_SUCCESS;
}

// Helper function.
void
getIteratorFromIndex(const unsigned int                                                          index,
                     const IteratorRangeDomainThreaderAssociate::DomainContainerType &           container,
                     IteratorRangeDomainThreaderAssociate::DomainContainerType::const_iterator & it)
{
  it = container.begin();
  for (unsigned int ii = 0; ii < index; ++ii)
  {
    ++it;
  }
}

void
setStartEnd(const unsigned int                                                     start,
            const unsigned int                                                     end,
            const IteratorRangeDomainThreaderAssociate::DomainContainerType &      container,
            IteratorRangeDomainThreaderAssociate::TestDomainThreader::DomainType & fullDomain)
{
  std::cout << std::endl << "From starting iterator index = " << start << " ending iterator index " << end << std::endl;
  IteratorRangeDomainThreaderAssociate::TestDomainThreader::DomainType::IteratorType beginIt;
  IteratorRangeDomainThreaderAssociate::TestDomainThreader::DomainType::IteratorType endIt;
  getIteratorFromIndex(start, container, beginIt);
  getIteratorFromIndex(end, container, endIt);

  const IteratorRangeDomainThreaderAssociate::TestDomainThreader::DomainType newDomain(beginIt, endIt);
  fullDomain = newDomain;
}
} // namespace

int
itkThreadedIteratorRangePartitionerTest(int, char *[])
{
  IteratorRangeDomainThreaderAssociate                                         enclosingClass;
  const IteratorRangeDomainThreaderAssociate::TestDomainThreader::ConstPointer domainThreader =
    enclosingClass.GetDomainThreader();

  /* Check # of threads */
  std::cout << "GetGlobalMaximumNumberOfThreads: "
            << domainThreader->GetMultiThreader()->GetGlobalMaximumNumberOfThreads() << std::endl;
  std::cout << "GetGlobalDefaultNumberOfThreads: "
            << domainThreader->GetMultiThreader()->GetGlobalDefaultNumberOfThreads() << std::endl;
  std::cout << "domainThreader->GetMultiThreader()->NumberOfWorkUnits(): "
            << domainThreader->GetMultiThreader()->GetNumberOfWorkUnits() << std::endl;

  using DomainType = IteratorRangeDomainThreaderAssociate::TestDomainThreader::DomainType;
  IteratorRangeDomainThreaderAssociate::DomainContainerType container(ITK_DEFAULT_MAX_THREADS + 110);
  for (unsigned int i = 0; i < ITK_DEFAULT_MAX_THREADS + 110; ++i)
  {
    container[i] = i;
  }
  DomainType fullDomain(container.begin(), container.end());

  /* Test with single thread */
  setStartEnd(0, 103, container, fullDomain);
  itk::ThreadIdType numberOfThreads = 1;
  if (ThreadedIteratorRangePartitionerRunTest(enclosingClass, numberOfThreads, fullDomain) != EXIT_SUCCESS)
  {
    return EXIT_FAILURE;
  }

  /* Test with range that doesn't start at 0 */
  setStartEnd(2, 105, container, fullDomain);
  numberOfThreads = 1;
  if (ThreadedIteratorRangePartitionerRunTest(enclosingClass, numberOfThreads, fullDomain) != EXIT_SUCCESS)
  {
    return EXIT_FAILURE;
  }

  /* Test with multiple threads */
  if (domainThreader->GetMultiThreader()->GetGlobalMaximumNumberOfThreads() > 1)
  {
    /* Test with default number of threads. */
    setStartEnd(6, 109, container, fullDomain);
    numberOfThreads = domainThreader->GetMultiThreader()->GetGlobalDefaultNumberOfThreads();
    if (ThreadedIteratorRangePartitionerRunTest(enclosingClass, numberOfThreads, fullDomain) != EXIT_SUCCESS)
    {
      return EXIT_FAILURE;
    }

    /* Test with max number of threads and check that we only used as
     * many as is reasonable. */
    const itk::ThreadIdType maxNumberOfThreads = domainThreader->GetMultiThreader()->GetGlobalMaximumNumberOfThreads();
    setStartEnd(6, 6 + maxNumberOfThreads, container, fullDomain);
    if (ThreadedIteratorRangePartitionerRunTest(enclosingClass, maxNumberOfThreads, fullDomain) != EXIT_SUCCESS)
    {
      return EXIT_FAILURE;
    }
    if (domainThreader->GetNumberOfWorkUnitsUsed() != maxNumberOfThreads)
    {
      std::cerr << "Error: Expected to use " << maxNumberOfThreads << "threads, but used "
                << domainThreader->GetNumberOfWorkUnitsUsed() << '.' << std::endl;
    }
  }
  else
  {
    std::cout << "No multi-threading available. " << std::endl;
  }

  return EXIT_SUCCESS;
}
