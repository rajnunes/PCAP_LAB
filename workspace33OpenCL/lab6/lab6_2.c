#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#define MAX_SOURCE 20000

int main ()
{
	int i, len, N;
	char *str = (char *) calloc (sizeof (char), 200);
//	for (i = 0; i < 100; i ++)
	//	str [i] = 'a';
	//str [i] = '\0';
	printf ("Enter number of times to echo and the string: ");
	scanf ("%d %[^\n]s", &N, str);
	//N = 3; strcpy (str, "Hello");
	char *newstr = (char *) calloc (sizeof (char), 200);
	for (len = 0; str [len] != '\0'; len ++);
	FILE *fp; char *source_str = (char *) calloc (sizeof (char), MAX_SOURCE); size_t source_size;
	if (! (fp = fopen ("strrepeat.cl", "r")))
	{
		perror ("File error."); return 0;
	}
	source_size = fread (source_str, 1, MAX_SOURCE, fp);
	fclose (fp);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint num_devices, num_platforms;
	cl_int status, datasize = sizeof (char) * len;

	status = clGetPlatformIDs(1, &platform_id, &num_platforms);
	status = clGetDeviceIDs (platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &num_devices);

	cl_context context = clCreateContext (NULL, 1, &device_id, NULL, NULL, &status);
	//printf ("Context returned %d\n", status);
	cl_command_queue cmdQueue = clCreateCommandQueue (context, device_id, NULL, &status);

	cl_mem original = clCreateBuffer (context, CL_MEM_READ_ONLY, datasize, NULL, &status);
	cl_mem modified = clCreateBuffer (context, CL_MEM_WRITE_ONLY, N * datasize, NULL, &status);

	status = clEnqueueWriteBuffer (cmdQueue, original, CL_TRUE, 0, datasize, str, 0, NULL, NULL);
	//printf ("WriteA returned %d\n", status);

	cl_program program = clCreateProgramWithSource (context, 1, &source_str, &source_size, &status);
	//printf ("Prog returned %d\n", status);
	status = clBuildProgram (program, 1, &device_id, 0, 0, 0);
	//printf ("Build returned %d\n", status);
	cl_kernel kernel = clCreateKernel (program, "strrepeat", &status);

	status = clSetKernelArg (kernel, 0, sizeof (original), &original);
	status = clSetKernelArg (kernel, 1, sizeof (modified), &modified);
	status = clSetKernelArg (kernel, 2, sizeof (int), &len);

	size_t global_item_size = N, local_item_size = 1;

	status = clEnqueueNDRangeKernel (cmdQueue, kernel, 1, 0, &global_item_size, &local_item_size, 0, 0, 0);
	//printf ("Exec returned %d\n", status);
	status = clFinish (cmdQueue);
	//printf ("Finish returned %d\n", status);
	status = clEnqueueReadBuffer (cmdQueue, modified, CL_TRUE, 0, N * datasize, newstr, 0, 0, 0);
	//printf ("Read returned %d\n", status);

	//printf ("N = %d\tlen = %d\n", N, len);
	newstr [N * len] = '\0';
	//for (i = 0; i < N * len; i ++)
		//printf ("%d = %d\n", i, newstr [i]);
	printf ("%s\n%s\n", str, newstr);
	status = clFlush (cmdQueue);
	status = clReleaseKernel (kernel);
	status = clReleaseProgram (program);
	status = clReleaseMemObject (modified);
	status = clReleaseMemObject (original);
	status = clReleaseCommandQueue (cmdQueue);
	status = clReleaseContext (context);

	free (str);
	free (newstr);
}

