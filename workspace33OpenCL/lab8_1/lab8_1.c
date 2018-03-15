#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SOURCE_SIZE (0x100000)

int isSpaceChar(int x){return x < 33 || x > 126;}

int main(void)
{
	char *A = (char*)malloc(sizeof(char) * 200);
	scanf("%[^\n]s", A);
	int n = strlen(A);

	FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("lab8_1.cl", "r");
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
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
												n * sizeof(int), NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
												n * sizeof(int), NULL, &ret);

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
									n * sizeof(int), A, 0, NULL, NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str,
													(const size_t*)&source_size, &ret);
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "sort_vector", &ret);

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);

	size_t global_item_size = n;
	size_t local_item_size = 1;

	char *B = (char*)malloc(sizeof(char*) * n);

	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size,
										&local_item_size, 0, NULL, NULL);
	ret = clFinish(command_queue);

	ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0,
								n * sizeof(int), B, 0, NULL, NULL);

	for(int i=0;i<n;i++)
		if(!isSpaceChar(B[i]))
			printf("%c ", B[i]);

	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(b_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	free(A);
	free(B);
	getchar();
	return 0;

}
