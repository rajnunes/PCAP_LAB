#include <stdio.h>
// #include <iostream>
#include <CL/cl.h>
#include <stdlib.h>
//Max source size of the kernel string
#define MAX_SOURCE_SIZE (0x100000)
int main(void)
{
// Create the two input vectors
	int i,N;
	int LIST_SIZE;

	char str[100];
	scanf("%s",str);
	printf("Enter N :" );
	scanf("%d",N);
	LIST_SIZE=strlen(str);
	//Initialize the input vectors
	// std::cout<<"hello";
	
	// Load the kernel source code into the array source_str
	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("q2_kernel.cl", "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to load kernel.\n");
		getchar();
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose( fp );
	// Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1,&device_id,
		&ret_num_devices);
	// Create an OpenCL context
	cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL,
		&ret);
	// Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context,
		device_id, NULL, &ret);
	// Create memory buffers on the device for each vector A, B and C
	cl_mem memStr = clCreateBuffer(context,
		CL_MEM_READ_WRITE,LIST_SIZE * sizeof(char), NULL, &ret);
	cl_mem memB = clCreateBuffer(context,
		CL_MEM_READ_WRITE,sizeof(int), NULL, &ret);
	cl_mem memT = clCreateBuffer(context,
		CL_MEM_READ_WRITE,LIST_SIZE*sizeof(int)*N, NULL, &ret);
	/*cl_mem memB = clCreateBuffer(context,
		CL_MEM_READ_ONLY,LIST_SIZE * sizeof(unsigned int), NULL, &ret);
	*/

	// Copy the lists A and B to their respective memory buffers
	ret = clEnqueueWriteBuffer(command_queue, memStr, CL_TRUE, 0,LIST_SIZE
		* sizeof(char), str, 0, NULL, NULL);

	ret = clEnqueueWriteBuffer(command_queue, memB, CL_TRUE, 0,LIST_SIZE
		* sizeof(char), N, 0, NULL, NULL);
	

	// Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context, 1,(const
		char**)&source_str, (const size_t *)&source_size, &ret);
	

	// Build the program
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	

	// Create the OpenCL kernel object
	cl_kernel kernel = clCreateKernel(program, "swap", &ret);
	

	// Set the arguments of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memStr);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&memB);

	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&memT);
	
	// Execute the OpenCL kernel on the array
	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;
	//Execute the kernel on the device
	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1,
		NULL,&global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clFinish(command_queue);



	// Read the memory buffer B on the device to the local variable B
	// int *B = (int*)malloc(sizeof(int)*LIST_SIZE);
	/*for (int i = 0; i < LIST_SIZE; ++i)
	{
		printf("%d\n",B[i] );
	}
	printf("\n");*/
	// char *T;
	ret = clEnqueueReadBuffer(command_queue, memT, CL_TRUE, 0,LIST_SIZE
		* sizeof(char), str, 0, NULL, NULL);
	// Display the result to the screen
	// for(i = 0; i < LIST_SIZE; i++)
		printf("%s ", str);
	// Clean up
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(memStr);
	// ret = clReleaseMemObject(memB);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	// free(str);
	// free(B);
	getchar();
	return 0;
}