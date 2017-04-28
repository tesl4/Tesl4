using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Azure.Batch;

namespace AzureBatchTaskProcessor1
{
    /// <summary>
    /// This class contains application-specific logic for splitting the job into
    /// tasks. The framework invokes the JobSplitter.Split method to obtain a
    /// sequence of tasks, which it adds to the job as the method returns them.
    ///
    /// This is the class where you will inject the logic of your job. Implement the
    /// Split method to return a sequence of CloudTask instances representing the
    /// tasks into which you want to partition the job.
    /// </summary>
    public class JobSplitter
    {
        private readonly IDictionary<string, string> _parameters;
        private readonly CloudJob _job;
        private readonly CloudTask _jobManagerTask;

        /// <summary>
        /// Initializes a new instance of the JobSplitter class. The JobSplitter
        /// class is constructed for you by the framework; you do not need to call
        /// the constructor yourself.
        /// </summary>
        public JobSplitter(CloudJob job, CloudTask jobManagerTask, IDictionary<string, string> parameters)
        {
            _job = job;
            _jobManagerTask = jobManagerTask;
            _parameters = parameters;
        }

        /// <summary>
        /// Gets the tasks into which to split the job. This is where you inject
        /// your application-specific logic for decomposing the job into tasks.
        ///
        /// The job manager framework invokes the Split method for you; you need
        /// only to implement it, not to call it yourself. Typically, your
        /// implementation should return tasks lazily, for example using a C#
        /// iterator and the "yield return" statement; this allows tasks to be added
        ///  and to start running while splitting is still in progress.
        /// </summary>
        /// <returns>The tasks to be added to the job. Tasks are added automatically
        /// by the job manager framework as they are returned by this method.</returns>
        public IEnumerable<CloudTask> Split()
        {
            // TODO: User will put their split logic here
            int startFrame = Convert.ToInt32(_parameters["StartFrame"]);
            int endFrame = Convert.ToInt32(_parameters["EndFrame"]);

            for (int i = startFrame; i <= endFrame; i++)
            {
                yield return new CloudTask("myTask" + i, "cmd /c dir");
            }
        }
    }
}