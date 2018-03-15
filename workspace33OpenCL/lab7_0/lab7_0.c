#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)
#define WA 3
#define HA 2
#define WB 3
#define HB 3
#define WC 3
#define HC 2
#define BLOCK_SIZE 1

int main()
{
	cl_int size_a = WA * HA;
	cl_int size_b = WB * HB;
	int* a = (int*) malloc(size_a * sizeof(int));
	int* b = (int*) malloc(size_b * sizeof(int));

	FILE *fp;
	char* source_str;
	size_t source_size;

	fp = fopen("lab7_0.cl", "r");
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

	for(int i=0;i<size_b;i++)
		scanf("%d", &b[i]);

	cl_int size_c = WC * HC;
	int* c = (int*) malloc(size_c * sizeof(int));

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
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, size_b * sizeof(int), NULL, &ret);
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size_c * sizeof(int), NULL, &ret);

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, size_a * sizeof(int), a, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, size_b * sizeof(int), b, 0, NULL, NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str,
																	(const size_t*)&source_size, &ret);

	ret = clBuildProgram (program, 1, &device_id, 0, 0, 0);
	cl_kernel kernel = clCreateKernel(program, "mat_mul", &ret);

	int widthA = WA;
	int widthB = WB;
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&c_mem_obj);
	ret = clSetKernelArg(kernel, 3, sizeof(cl_int), (void*)&widthA);
	ret = clSetKernelArg(kernel, 4, sizeof(cl_int), (void*)&widthB);
	size_t localWorkSize[2] = {BLOCK_SIZE, BLOCK_SIZE};
	size_t globalWorkSize[2] = {WC, HC};

	ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	clFinish(command_queue);

	ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, size_c * sizeof(int), c, 0, NULL, NULL);

	for(int i=0;i<size_c;i++)
	{
		printf("%d ", c[i]);
		if(i % WC == WC - 1)
			printf("\n");
	}

	free(source_str);
	clReleaseContext(context);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(command_queue);
	getchar();

}
