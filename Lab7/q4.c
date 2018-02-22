#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
//Max source size of the kernel string
#define MAX_SOURCE_SIZE (0x100000)
//Width and height of matrices
#define WA 3
#define HA 3
#define WB 3
#define HB 3
#define WC 3
#define HC 2
#define BLOCK_SIZE 1
int main(void)
{
	unsigned int size_A = WA * HA;
	unsigned int size_B = WB * HB;
	int* a = (int*) malloc(size_A*sizeof(int));
	int* c = (int*) malloc(size_A*sizeof(int));
	FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("q4_kernel.cl", "r");
	if (!fp) {
		fprintf(stderr, "Failed to load kernel.\n");
		getchar();
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose( fp ); //Close file pointer
	int i;
	for(i=0;i<size_A;i++){
		scanf("%d",&a[i]);
		c[i]=-2;
	}

// Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1,&device_id,
		&ret_num_devices);
	// Create an OpenCL context
	cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
	// Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id,NULL,&ret);
	cl_program	clProgram = clCreateProgramWithSource(context, 1,(const char
		**)&source_str, (const size_t *)&source_size, &ret);
	ret = clBuildProgram(clProgram, 0, NULL, NULL, NULL, NULL);
	// Create memory buffers on the device for each vector
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
		size_A*sizeof(int), NULL, &ret);
	
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
		size_A*sizeof(int), NULL, &ret);
	/*cl_mem c_mem_obj = clCreateBuffer(context,
		CL_MEM_WRITE_ONLY,size_A*sizeof(int), NULL, &ret);*/
	// Copy the lists A and B to their respective memory buffers
	
	ret	=clEnqueueWriteBuffer(command_queue,a_mem_obj,CL_TRUE,
		0,size_A*sizeof(int),a , 0, NULL, NULL);
	/*ret = clEnqueueWriteBuffer(command_queue, b_mem_obj,CL_TRUE,
		0,size_B*sizeof(int),b , 0, NULL, NULL);*/
	// Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context,1,
		(const char**)&source_str, (const size_t *)&source_size, &ret);


	// Build the program
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	/*if(ret!=CL_SUCCESS){
		char buff[2048];
		int len;
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buff), buff,&len);
		printf("%s\n",buff );
		exit(1);
	}*/

	// Create the OpenCL kernel
	cl_kernel kernel = clCreateKernel(program, "mat_pow", &ret);
	// Set the arguments of the kernel
	int widthA = WA;
	int widthB = WB;
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
	/*ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
	ret = clSetKernelArg(kernel, 4, sizeof(int), (void *)&widthB);
	*/ret = clSetKernelArg(kernel, 2, sizeof(int), (void *)&widthA);

	size_t globalWorkSize[2]= {HA,WA};
	size_t localWorkSize[2]={BLOCK_SIZE,BLOCK_SIZE};
	cl_event event;
	ret
	=
	clEnqueueNDRangeKernel(command_queue, kernel,2,NULL,globalWorkSize, localWorkSize, 0, NULL,NULL);
	clFinish(command_queue);
	ret = clEnqueueReadBuffer(command_queue,b_mem_obj, CL_TRUE,0,size_A*sizeof(int), c, 0, NULL, NULL);
	
	printf("\nMatrix C\n");
	for(int i = 0; i < size_A; i++)
	{
		printf("%d\t", c[i]);
		if(((i + 1) % WA) == 0)
			printf("\n");
	}
	free(source_str);
	clReleaseContext(context);
	clReleaseKernel(kernel);
	clReleaseProgram(clProgram);
	clReleaseCommandQueue(command_queue);
	getchar();
}
