using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Azure.Batch;

namespace AzureBatchTaskProcessor1.Framework
{
    /// <summary>
    /// This class is responsible to adding tasks returned by the job splitter to
    /// the Azure Batch job.  The JobManager class splits up the sequence of tasks
    /// into batches, then calls TaskSubmitter.SubmitTasks on a background thread
    /// for each batch.
    /// </summary>
    public static class TaskSubmitter
    {
        /// <summary>
        /// Adds a collection of tasks to the job identified by the Configuration class.
        /// </summary>
        public static void SubmitTasks(IEnumerable<CloudTask> tasks, Configuration configuration)
        {
            try
            {
                using (var batchClient = configuration.GetBatchClient())
                {
                    batchClient.JobOperations.AddTask(configuration.JobId, tasks);
                }
            }
            catch (BatchClientException ex)
            {
                throw new JobManagerException($"Couldn't add tasks to the job - terminating job manager: \r\n {ex.ToString()}", ex);
            }
            catch (ParallelOperationsException ex)
            {
                throw new JobManagerException($"Couldn't add tasks to the job - terminating job manager: \r\n {ex.ToString()}", ex);
            }
        }
    }
}