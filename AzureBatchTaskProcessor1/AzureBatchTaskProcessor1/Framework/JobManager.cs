using System;
using System.Collections.Generic;
using System.Reactive.Linq;
using System.Threading.Tasks;
using Microsoft.Azure.Batch;

namespace AzureBatchTaskProcessor1.Framework
{
    /// <summary>
    /// This class orchestrates the components of the job manager program. It is
    /// responsible for initialising the job splitter, invoking the job splitter,
    /// and dispatching the tasks returned by the job splitter to the TaskSubmitter.
    /// </summary>
    internal class JobManager
    {
        private static readonly TimeSpan TaskSubmissionInterval = TimeSpan.FromSeconds(2.0);
        private JobSplitter _jobSplitter;
        private CloudJob _cloudJob;
        private CloudTask _cloudTask;
        private Configuration _configuration = new Configuration();

        /// <summary>
        /// Runs the job manager. This method is responsible for orchestrating the
        /// other components of the project -- initializing the job splitter,
        /// invoking the job splitter, and passing the tasks returned by the job
        /// splitter to the TaskSubmitter.
        /// </summary>
        public async Task RunJobManagerTask()
        {
            await LoadJobSplitter();
            await SplitAndSubmitTasks();
        }

        /// <summary>
        /// Adds the job's tasks to the job, by invoking the job splitter and
        /// passing the returned tasks to the TaskSubmitter.
        ///
        /// In order to allow tasks to be added to the Azure Batch job without
        /// blocking the job splitter as it creates further tasks, this method uses
        /// Reactive Extensions to treat the sequence of tasks as an IObservable and
        /// to act on the tasks in the background as they are generated.
        ///
        /// The Rx Buffer method is used to collect tasks into batches for efficient
        /// submission to Azure Batch, and the Rx Do method then passes these
        /// batches to the TaskSubmitter.
        /// </summary>
        private async Task SplitAndSubmitTasks()
        {
            try
            {
                await _jobSplitter.Split()
                    .ToObservable()
                    .Buffer(TaskSubmissionInterval)
                    .Do(tasks => TaskSubmitter.SubmitTasks(tasks, _configuration))
                    .DefaultIfEmpty();
            }
            catch (Exception ex)
            {
                throw new JobManagerException($"{ex.GetType().Name} exception in job splitter: {ex.Message} - terminating job manager.", ex);
            }
        }

        /// <summary>
        /// Instantiates the job splitter defined in your custom code, with the job
        /// context and parameters loaded by the framework.
        /// </summary>
        private async Task LoadJobSplitter()
        {
            await LoadJobAndTask();
            var jobParameters = _configuration.GetJobParameters();
            _jobSplitter = new JobSplitter(_cloudJob, _cloudTask, jobParameters);
        }

        /// <summary>
        /// Loads the Azure Batch job and job manager task information.
        /// </summary>
        private async Task LoadJobAndTask()
        {
            try
            {
                using (var batchclient = _configuration.GetBatchClient())
                {
                    _cloudJob = await batchclient.JobOperations.GetJobAsync(_configuration.JobId);
                    _cloudTask = await batchclient.JobOperations.GetTaskAsync(_configuration.JobId, _configuration.TaskId);
                }
            }
            catch (BatchClientException ex)
            {
                throw new JobManagerException($"Couldn't retrieve job or task details from Azure Batch - terminating job manager.\r\n{ex.RequestInformation.BatchError}", ex);
            }
        }
    }
}