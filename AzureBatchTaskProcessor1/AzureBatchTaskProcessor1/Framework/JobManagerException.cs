using System;
using System.Runtime.CompilerServices;
using System.Runtime.Serialization;

namespace AzureBatchTaskProcessor1.Framework
{
    /// <summary>
    /// Represents an error that requires the job manager to terminate.
    /// JobManagerException is used to wrap 'expected' errors where specific
    /// diagnostic information can be provided as part of termination. 
    /// </summary>
    [Serializable]
    public sealed class JobManagerException : Exception
    {
        public JobManagerException(string message)
            : base(message)
        {
        }

        public JobManagerException(string message, Exception innerException)
            : base(message, innerException)
        {
        }

        private JobManagerException(SerializationInfo info, StreamingContext context) : base(info, context)
        {
        }
    }
}