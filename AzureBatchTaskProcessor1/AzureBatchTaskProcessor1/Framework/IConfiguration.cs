using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.WindowsAzure.Storage;
using Microsoft.Azure.Batch;

namespace AzureBatchTaskProcessor1.Framework
{
    public interface IConfiguration
    {
        /// <summary>
        /// Gets the ID of the job.
        /// </summary>
        string JobId
        {
            get;
        }

        /// <summary>
        /// Gets the ID of the task.
        /// </summary>
        string TaskId
        {
            get;
        }

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
        IDictionary<string, string> GetJobParameters();

        /// <summary>
        /// Gets the Azure storage account to use for persisting task outputs.
        /// </summary>
        CloudStorageAccount StorageAccount
        {
            get;
        }
    }
}
