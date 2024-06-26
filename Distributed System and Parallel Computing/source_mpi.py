import cv2
import numpy as np
import os
import time
import matplotlib.pyplot as plt
from mpi4py import MPI
import concurrent.futures
import os

# ---------- Input to set number of image samples ----------
def input_image_sample():
    while True:
        print("Choose an option:")
        print("1. Run with 100 image samples")
        print("2. Run with 200 image samples")
        print("3. Run with 350 image samples")

        user_input = input("Enter your choice (1/2/3): ")

        if user_input in ["1", "2", "3"]:
            # Convert the user input to an integer
            choice = int(user_input)

            if choice == 1:
                print("\nRun with 100 images\n")
                return "100"
            elif choice == 2:
                print("\nRun with 200 images\n")
                return "200"
            elif choice == 3:
                print("\nRun with 350 images\n")
                return "350"

            # Exit the loop once a valid choice is made
            break
        else:
            print("Invalid choice. Please enter 1, 2, or 3.\n")
# ---------- Input to set number of image samples ----------


# ---------- Process image using Gaussian Filter ----------
def process_gaussian_filter(image):
    # Your image processing logic here
    kernel_size = 5  # Must be an odd number
    sigma = 1.0
    kx = cv2.getGaussianKernel(kernel_size, sigma)
    ky = cv2.getGaussianKernel(kernel_size, sigma)
    kernel = np.multiply(kx, np.transpose(ky))
    blurred_image_output = cv2.filter2D(image, -1, kernel)

    # Resize parameters
    desired_width = 500

    # Resize the original image for display
    resized_image = cv2.resize(image, (desired_width, int(image.shape[0] * (desired_width / image.shape[1]))))
    # Resize the gaussian image for display
    resized_gaussian_image = cv2.resize(blurred_image_output, (desired_width, int(blurred_image_output.shape[0] * (desired_width / blurred_image_output.shape[1]))))

    return resized_gaussian_image

# ---------- Process image using Gaussian Filter ----------


# ---------- Process image using Bilateral Filter ----------
def gaussian(x,sigma):
    return (1.0/(2*np.pi*(sigma**2)))*np.exp(-(x**2)/(2*(sigma**2)))

def distance(x1,y1,x2,y2):
    return np.sqrt(np.abs((x1-x2)**2-(y1-y2)**2))

def process_bilateral_filter(image):
    # Apply bilateral filter
        diameter = 9     # Diameter of each pixel neighborhood to consider
        sigma_i = 75     # Intensity similarity weight
        sigma_s = 75     # Spatial distance weight
        blurred_image_output = cv2.bilateralFilter(image, diameter, sigma_i, sigma_s)

        # Resize parameters
        desired_width = 500

        # Resize the original image for display
        resized_image = cv2.resize(image, (desired_width, int(image.shape[0] * (desired_width / image.shape[1]))))
        # Resize the convolution image for display
        resized_bilateral_image = cv2.resize(blurred_image_output, (desired_width, int(blurred_image_output.shape[0] * (desired_width / blurred_image_output.shape[1]))))

        return resized_bilateral_image

# ---------- Process image using Bilateral Filter ----------


#---------- Gaussian Filter using MPI ----------
def mpi_gaussian_filter_image(image_directory, image_files, num_image):

    # Specify the paths for the gaussian output directories 
    gaussian_output_directory = os.path.join(image_directory, "gaussian_filter_image")

    # Create the gaussian output directory if it doesn't exist
    if not os.path.exists(gaussian_output_directory):
        os.makedirs(gaussian_output_directory)

    # Initialize MPI
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    # Calculate the number of files per process
    files_per_process = len(image_files) // size
    remainder = len(image_files) % size

    # Calculate the starting index for this process
    start_index = rank * files_per_process + min(rank, remainder)

    # Determine the ending index for this process
    end_index = start_index + files_per_process + (1 if rank < remainder else 0)

    # Extract the image files assigned to this process
    image_files_per_process = image_files[start_index:end_index]

    # Load all images once and distribute them to all processes
    images_per_process = []
    for image_file in image_files_per_process:
        image_path = os.path.join(image_directory, image_file)
        image = cv2.imread(image_path)
        if image is not None:
            images_per_process.append((image_file, image))

    # Synchronize all processes
    comm.Barrier()

    # Start the timer
    total_start_time = MPI.Wtime()

    # Process images assigned to this process
    processed_images = []
    counter = 0

    for image_file, image in images_per_process:
        start_time = time.time()

        processed_image = process_gaussian_filter(image)
        processed_images.append((image_file, processed_image))

        counter += 1

        # Save the blurred image to the output directory
        output_path = os.path.join(gaussian_output_directory, f"gaussian_{image_file}")
        cv2.imwrite(output_path, processed_image)

        end_time = time.time()
        each_total_time = end_time - start_time
        
        # Output time taken for each image
        print(f"{counter} - [{image_file}] Total time taken: {each_total_time:.4f} seconds")

    # Stop the timer
    total_end_time = MPI.Wtime()

    # Calculate the total time
    total_time = total_end_time - total_start_time

    # MPI Output Result
    print("\n---------- MPI Result ----------")
    print(f"Total time taken for running {num_image} images using gaussian filter in MPI: {total_time:.4f} seconds\n")

    # Gather the execution times from all processes to rank 0
    execution_times = comm.gather(total_end_time - total_start_time, root=0)

    # Rank 0 collects and analyzes the execution times
    if rank == 0:
        print("\nBenchmark Results:")
        for i, execution_time in enumerate(execution_times):
            num_processes = i + 1
            average_execution_time = execution_time / num_processes
            print(f"Processes: {num_processes}, Average Execution Time: {average_execution_time:.4f} seconds")

    # Finalize MPI
    MPI.Finalize()
#---------- Gaussian Filter using MPI ----------


#---------- Bilateral Filter using MPI ----------
def mpi_bilateral_filter_image(image_directory, image_files, num_image):
    
    # Specify the paths for the bilateral output directories 
    bilateral_output_directory = os.path.join(image_directory, "bilateral_filter_image")

    # Create the bilateral output directory if it doesn't exist
    if not os.path.exists(bilateral_output_directory):
        os.makedirs(bilateral_output_directory)

    # Initialize MPI
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    # Calculate the number of files per process
    files_per_process = len(image_files) // size
    remainder = len(image_files) % size

    # Calculate the starting index for this process
    start_index = rank * files_per_process + min(rank, remainder)

    # Determine the ending index for this process
    end_index = start_index + files_per_process + (1 if rank < remainder else 0)

    # Extract the image files assigned to this process
    image_files_per_process = image_files[start_index:end_index]

    # Load all images once and distribute them to all processes
    images_per_process = []
    for image_file in image_files_per_process:
        image_path = os.path.join(image_directory, image_file)
        image = cv2.imread(image_path)
        if image is not None:
            images_per_process.append((image_file, image))

    # Synchronize all processes
    comm.Barrier()

    # Start the timer
    total_start_time = MPI.Wtime()

    # Process images assigned to this process
    processed_images = []
    counter = 0

    for image_file, image in images_per_process:
        start_time = time.time()

        processed_image = process_bilateral_filter(image)
        processed_images.append((image_file, processed_image))

        counter += 1

        # Save the blurred image to the output directory
        output_path = os.path.join(bilateral_output_directory, f"bilateral_{image_file}")
        cv2.imwrite(output_path, processed_image)

        end_time = time.time()
        each_total_time = end_time - start_time

        # Output time taken for each image
        print(f"{counter} - [{image_file}] Total time taken: {each_total_time:.4f} seconds")

    # Stop the timer
    total_end_time = MPI.Wtime()

    # Calculate the total time
    total_time = total_end_time - total_start_time

    # MPI Output Result
    print("\n---------- MPI Result ----------")
    print(f"Total time taken for running {num_image} images using bilateral filter in MPI: {total_time:.4f} seconds\n")

    # Gather the execution times from all processes to rank 0
    execution_times = comm.gather(total_end_time - total_start_time, root=0)

    # Rank 0 collects and analyzes the execution times
    if rank == 0:
        print("\nBenchmark Results:")
        for i, execution_time in enumerate(execution_times):
            num_processes = i + 1
            average_execution_time = execution_time / num_processes
            print(f"Processes: {num_processes}, Average Execution Time: {average_execution_time:.4f} seconds")

    # Finalize MPI
    MPI.Finalize()
#---------- Bilateral Filter using MPI ----------


def main():

    print("\n*************** MPI ***************\n")

    # Get the directory of the current script
    script_directory = os.path.dirname(os.path.abspath(__file__))

    num_image = input_image_sample()

    # Directory containing the original images
    image_directory = os.path.join(script_directory, "dataset", num_image + "_images") # Run for 100 images

    # List all files in the directory
    image_files = [file for file in os.listdir(image_directory) if file.lower().endswith(('.jpg', '.png', '.jpeg'))]

    # Choose to run Gaussian or Bilateral filters
    while True:
        print("Choose an option:")
        print("1. Run " + num_image + " images using Gaussian Filter")
        print("2. Run " + num_image + " images using Bilateral Filter")

        user_input = input("Enter your choice (1/2): ")

        if user_input in ["1", "2"]:
            # Convert the user input to an integer
            choice = int(user_input)

            if choice == 1:
                print("\nRun " + num_image + " images using Gaussian Filter in MPI\n")
                mpi_gaussian_filter_image(image_directory, image_files, num_image)
            elif choice == 2:
                print("\nRun " + num_image + " images using Bilateral Filter in MPI\n")
                mpi_bilateral_filter_image(image_directory, image_files, num_image)

            # Exit the loop once a valid choice is made
            break
        else:
            print("Invalid choice. Please enter 1, 2.\n")


if __name__ == "__main__":
    main()

