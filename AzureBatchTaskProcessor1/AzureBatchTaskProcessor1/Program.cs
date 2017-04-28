using System;
using AzureBatchTaskProcessor1.Framework;

namespace AzureBatchTaskProcessor1
{
    class Program
    {
        static int Main(string[] args)
        {
            try
            {
                var jobManager = new JobManager();
                jobManager.RunJobManagerTask().GetAwaiter().GetResult();
                return 0;
            }
            catch (JobManagerException ex)
            {
                Console.Error.WriteLine(ex.ToString());
                return 1;
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine(ex.ToString());
                return 2;
            }
        }
    }
}
