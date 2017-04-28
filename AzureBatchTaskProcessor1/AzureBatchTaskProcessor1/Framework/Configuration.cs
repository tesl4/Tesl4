using System;
using System.Collections.Generic;
using System.IO;
using Microsoft.Azure.Batch;
using Microsoft.Azure.Batch.Auth;
using Microsoft.WindowsAzure.Storage;
using Microsoft.WindowsAzure.Storage.Auth;
using Newtonsoft.Json;

namespace AzureBatchTaskProcessor1.Framework
{
    /// <summary>
    /// Provides configuration information about the job, job manager task, Batch account, and storage account.
    /// </summary>
    public class Configuration : IConfiguration
    {
        /// <summary>
        /// Gets a BatchClient instance for working with the Batch account to which
        /// the job belongs.  This uses the Batch account URL and key provided in
        /// environment variables (see the Credentials property for details).
        /// </summary>
        public BatchClient GetBatchClient()
        {
            return BatchClient.Open(Credentials);
        }

        private const string ParameterFile = "Parameters.json";

        /// <summary>
        /// Gets the job parameters. In this job manager implementation, clients
        /// supply parameters as a resource file named "parameters.json" on the job
        /// manager task, where each 'property' in the JSON object is mapped to a dictionary entry.
        ///
        /// Job submitters are not required to provide a parameters collection
        /// (parameters.json file); if they don't, the parameters collection is empty.
        ///
        /// The semantics of the parameters are up to the job manager
        /// implementation; the Batch service does not ascribe meaning to any parameter.
        /// </summary>
        /// <returns>The job parameters, as read from the "parameters.json" resource
        ///  file; or an empty collection if there is no "parameters.json" file.</returns>
        public IDictionary<string, string> GetJobParameters()
        {
            try
            {
                var jsonString = File.Exists(ParameterFile) ? File.ReadAllText(ParameterFile) : string.Empty;

                return JsonConvert.DeserializeObject<Dictionary<string, string>>(jsonString);
            }
            catch (Exception ex) when (ex is JsonSerializationException || ex is JsonReaderException)
            {
                throw new JobManagerException($"Couldn't parse job parameters - terminating job manager. {ex.Message}", ex);
            }
        }

        /// <summary>
        /// Gets the ID of the job.
        /// </summary>
        public string JobId => EnvironmentVariables.JobId;

        /// <summary>
        /// Gets the ID of the job manager task.
        /// </summary>
        public string TaskId => EnvironmentVariables.TaskId;

        /// <summary>
        /// Evaluates the credentials for the Azure Batch account.
        /// </summary>
        private static Lazy<BatchSharedKeyCredentials> _credentials = new Lazy<BatchSharedKeyCredentials>(() =>
        {
            if (string.IsNullOrEmpty(Environment.GetEnvironmentVariable("YOUR_BATCH_URL")))
            {
                throw new JobManagerException("Environment variable \"YOUR_BATCH_URL\" is not supplied.");
            }

            if (string.IsNullOrEmpty(Environment.GetEnvironmentVariable("YOUR_BATCH_KEY")))
            {
                throw new JobManagerException("Environment variable \"YOUR_BATCH_KEY\" is not supplied.");
            }

            return new BatchSharedKeyCredentials(
                Environment.GetEnvironmentVariable("YOUR_BATCH_URL"),
                Environment.GetEnvironmentVariable("AZ_BATCH_ACCOUNT_NAME"),
                Environment.GetEnvironmentVariable("YOUR_BATCH_KEY"));
        });

        /// <summary>
        /// Gets the credentials for the Azure Batch account. These are used for
        /// adding tasks to the Azure Batch job as the tasks are returned by the job splitter.
        /// </summary>
        private static BatchSharedKeyCredentials Credentials => _credentials.Value;

        private static Lazy<CloudStorageAccount> _storageAccount = new Lazy<CloudStorageAccount>(() =>
        {
            if (string.IsNullOrEmpty(Environment.GetEnvironmentVariable("LINKED_STORAGE_ACCOUNT")))
            {
                throw new JobManagerException("Environment variable \"LINKED_STORAGE_ACCOUNT\" is not supplied.");
            }

            if (string.IsNullOrEmpty(Environment.GetEnvironmentVariable("LINKED_STORAGE_KEY")))
            {
                throw new JobManagerException("Environment variable \"LINKED_STORAGE_KEY\" is not supplied.");
            }

            return new CloudStorageAccount(
                new StorageCredentials(Environment.GetEnvironmentVariable("LINKED_STORAGE_ACCOUNT"),
                    Environment.GetEnvironmentVariable("LINKED_STORAGE_KEY")), true);
        });

        /// <summary>
        /// Gets the Azure storage account to use for persisting task outputs.
        /// </summary>
        public CloudStorageAccount StorageAccount => _storageAccount.Value;

        /// <summary>
        /// Provides access to environment variables provided by the Batch service.
        /// </summary>
        public static class EnvironmentVariables
        {
            /// <summary>
            /// Gets the ID of the job containing the task.
            /// </summary>
            public static string JobId => Environment.GetEnvironmentVariable("AZ_BATCH_JOB_ID");

            /// <summary>
            /// Gets the ID of the task.
            /// </summary>
            public static string TaskId => Environment.GetEnvironmentVariable("AZ_BATCH_TASK_ID");

            /// <summary>
            /// Gets the name of the account to which the task belongs.
            /// </summary>
            public static string AccountName => Environment.GetEnvironmentVariable("AZ_BATCH_ACCOUNT_NAME");

            /// <summary>
            /// Gets the full path of the job preparation task directory on the node.
            /// </summary>
            public static string JobPreparationDirectory => Environment.GetEnvironmentVariable("AZ_BATCH_JOB_PREP_DIR");

            /// <summary>
            /// Gets the full path of the job preparation task working directory on the node.
            /// </summary>
            public static string JobPreparationWorkingDirectory => Environment.GetEnvironmentVariable("AZ_BATCH_JOB_PREP_WORKING_DIR");

            /// <summary>
            /// Gets the ID of the node on which the task is running.
            /// </summary>
            public static string NodeId => Environment.GetEnvironmentVariable("AZ_BATCH_NODE_ID");

            /// <summary>
            /// Gets the root of the part of the file system available to the Batch service.
            /// </summary>
            public static string NodeRootDirectory => Environment.GetEnvironmentVariable("AZ_BATCH_NODE_ROOT_DIR");

            /// <summary>
            /// Gets the full path of the shared directory on the node.
            /// </summary>
            public static string NodeSharedDirectory => Environment.GetEnvironmentVariable("AZ_BATCH_NODE_SHARED_DIR");

            /// <summary>
            /// Gets the full path of the start task directory on the node.
            /// </summary>
            public static string NodeStartupDirectory => Environment.GetEnvironmentVariable("AZ_BATCH_NODE_STARTUP_DIR");

            /// <summary>
            /// Gets the ID of the pool on which the task is running.
            /// </summary>
            public static string PoolId => Environment.GetEnvironmentVariable("AZ_BATCH_POOL_ID");

            /// <summary>
            /// Gets the full path of the task directory on the node.
            /// </summary>
            public static string TaskDirectory => Environment.GetEnvironmentVariable("AZ_BATCH_TASK_DIR");

            /// <summary>
            /// Gets the full path of the task working directory on the node.
            /// </summary>
            public static string TaskWorkingDirectory => Environment.GetEnvironmentVariable("AZ_BATCH_TASK_WORKING_DIR");
        }
    }
}
