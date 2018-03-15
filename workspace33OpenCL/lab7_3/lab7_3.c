#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	cl_int size_a = n * m;
	cl_int size_b = n * m;
	int* a = (int*) malloc(size_a * sizeof(int));
	int* b = (int*) malloc(size_b * sizeof(int));

	FILE *fp;
	char* source_str;
	size_t source_size;

	fp = fopen("lab7_3.cl", "r");
	if(!fp)
	{
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	source_str = (char*) malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);

	fclose(fp);
	for(int i=0;i<size_a;i++)
		scanf("%d", &a[i]);


	// cl
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);

	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, size_a * sizeof(int), NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size_b * sizeof(int), NULL, &ret);

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, size_a * sizeof(int), a, 0, NULL, NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str,
																	(const size_t*)&source_size, &ret);

	ret = clBuildProgram (program, 1, &device_id, 0, 0, 0);
	cl_kernel kernel = clCreateKernel(program, "transpose", &ret);

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_int), (void*)&n);
	ret = clSetKernelArg(kernel, 3, sizeof(cl_int), (void*)&m);
	size_t localWorkSize[2] = {1, 1};
	size_t globalWorkSize[2] = {n, m};

	ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	clFinish(command_queue);

	ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0, size_b * sizeof(int), b, 0, NULL, NULL);

	for(int i=0;i<size_b;i++)
	{
		printf("%d ", b[i]);
		if(i % n == n - 1)
			printf("\n");
	}

	free(source_str);
	clReleaseContext(context);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(command_queue);
	getchar();

}
