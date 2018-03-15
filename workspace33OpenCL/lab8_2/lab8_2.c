#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)

int main(void)
{
	int n;
	scanf("%d", &n);
	int *A = (int*)malloc(sizeof(int) * n);
	for(int i=0;i<n;i++)
		scanf("%d", &A[i]);

	FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("lab8_2.cl", "r");
	if(!fp)
	{
		printf("ERR");
		exit(1);
	}

	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU,
							1, &device_id, &ret_num_devices);

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,
												n * sizeof(int), NULL, &ret);

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
									n * sizeof(int), A, 0, NULL, NULL);

	cl_program program1 = clCreateProgramWithSource(context, 1, (const char**)&source_str,
													(const size_t*)&source_size, &ret);
	cl_program program2 = clCreateProgramWithSource(context, 1, (const char**)&source_str,
													(const size_t*)&source_size, &ret);

	ret = clBuildProgram(program1, 1, &device_id, NULL, NULL, NULL);
	ret = clBuildProgram(program2, 1, &device_id, NULL, NULL, NULL);

	cl_kernel kernel1 = clCreateKernel(program1, "odd", &ret);
	cl_kernel kernel2 = clCreateKernel(program2, "even", &ret);

	ret = clSetKernelArg(kernel1, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel2, 0, sizeof(cl_mem), (void*)&a_mem_obj);

	size_t global_item_size = n;
	size_t local_item_size = 1;

	for(int i=0;i<(n + 1)/2;i++)
	{
		ret = clEnqueueNDRangeKernel(command_queue, kernel1, 1, NULL, &global_item_size,
											&local_item_size, 0, NULL, NULL);

		ret = clEnqueueNDRangeKernel(command_queue, kernel2, 1, NULL, &global_item_size,
											&local_item_size, 0, NULL, NULL);
	}

	ret = clFinish(command_queue);
	ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
								n * sizeof(int), A, 0, NULL, NULL);

	for(int i=0;i<n;i++)
		printf("%d ", A[i]);

	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel1);
	ret = clReleaseKernel(kernel2);
	ret = clReleaseProgram(program1);
	ret = clReleaseProgram(program2);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	free(A);
	getchar();
	return 0;

}
