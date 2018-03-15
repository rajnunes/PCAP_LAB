#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SOURCE 20000

int main ()
{
	int i, len, word = -1, start [10] = {0}, end [10] = {0};
	char *str = (char *) calloc (sizeof (char), 200);
	//for (i = 0; i < 100; i ++)
		//str [i] = 'a';
	//str [i] = '\0';
	printf ("Enter string: ");
	scanf ("%[^\n]s", str);
	//printf ("Entered %s\n", str);
	char *newstr = (char *) calloc (sizeof (char), 200);
	for (i = 0; str [i] != '\0'; i ++)
	{
	//	printf ("\ni = %d, char = %c ", i, str [i]);
		if (isalnum (str [i]))
		{
		//	printf ("is alnum");
			if (isspace (str [i - 1]) || i == 0)
				start [++word] = i;
		}
		else
		{
			//printf ("is not alnum");
			if (isalnum(str [i - 1]))
				end [word] = i - 1;
		}
	}
	if (end [word] == 0)
		end [word] = i - 1;
	word ++; len = i;
	//printf ("WORD = %d, len = %d \n", word, len);
	//for (int i = 0; i < word; i ++)
		//printf ("%d: %d -> %d\n", i + 1, start [i], end [i]);

	FILE *fp; char *source_str = (char *) calloc (sizeof (char), MAX_SOURCE); size_t source_size;
	if (! (fp = fopen ("wordrev.cl", "r")))
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
	//printf ("CmdQueue returned %d\n", status);

	cl_mem original = clCreateBuffer (context, CL_MEM_READ_ONLY, datasize, NULL, &status);
	//printf ("Make orig returned %d\n", status);
	cl_mem modified = clCreateBuffer (context, CL_MEM_WRITE_ONLY, datasize, NULL, &status);
	//printf ("Make modi returned %d\n", status);
	cl_mem startBuf = clCreateBuffer (context, CL_MEM_READ_ONLY, word * sizeof (int), NULL, &status);
	//printf ("Make start returned %d\n", status);
	cl_mem endBuf = clCreateBuffer (context, CL_MEM_READ_ONLY, word * sizeof (int), NULL, &status);
	//printf ("Make end returned %d\n", status);

	status = clEnqueueWriteBuffer (cmdQueue, original, CL_TRUE, 0, datasize, str, 0, NULL, NULL);
	//printf ("WriteA returned %d\n", status);
	status = clEnqueueWriteBuffer (cmdQueue, startBuf, CL_TRUE, 0, word * sizeof (int), start, 0, NULL, NULL);
	//printf ("WriteStart returned %d\n", status);
	status = clEnqueueWriteBuffer (cmdQueue, endBuf, CL_TRUE, 0, word * sizeof (int), end, 0, NULL, NULL);
	//printf ("WriteEnd returned %d\n", status);

	cl_program program = clCreateProgramWithSource (context, 1, &source_str, &source_size, &status);
	//printf ("Prog returned %d\n", status);
	status = clBuildProgram (program, 1, &device_id, 0, 0, 0);
	//printf ("Build returned %d\n", status);
	cl_kernel kernel = clCreateKernel (program, "wordrev", &status);

	status = clSetKernelArg (kernel, 0, sizeof (original), &original);
	status = clSetKernelArg (kernel, 1, sizeof (modified), &modified);
	status = clSetKernelArg (kernel, 2, sizeof (startBuf), &startBuf);
	status = clSetKernelArg (kernel, 3, sizeof (endBuf), &endBuf);

	size_t global_item_size = word, local_item_size = 1;

	status = clEnqueueNDRangeKernel (cmdQueue, kernel, 1, 0, &global_item_size, &local_item_size, 0, 0, 0);
	//printf ("Exec returned %d\n", status);
	status = clFinish (cmdQueue);
	//printf ("Finish returned %d\n", status);
	status = clEnqueueReadBuffer (cmdQueue, modified, CL_TRUE, 0, datasize, newstr, 0, 0, 0);
	//printf ("Read returned %d\n", status);
	newstr [len] = '\0';
	for (i = 0; i < len; i ++)
		//printf ("%d = %d %c\n", i, newstr [i], newstr [i]);
		if (newstr [i] == 0)
			newstr [i] = str [i];
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

