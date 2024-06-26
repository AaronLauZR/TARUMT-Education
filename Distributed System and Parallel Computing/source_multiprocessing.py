import cv2
import numpy as np
import os
import time
from multiprocessing import Pool
import matplotlib.pyplot as plt
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

            if user_input == "1":
                print("\nRun with 100 images\n")
                return "100"
            elif user_input == "2":
                print("\nRun with 200 images\n")
                return "200"
            elif user_input == "3":
                print("\nRun with 350 images\n")
                return "350"

            # Exit the loop once a valid choice is made
            break
        else:
            print("Invalid choice. Please enter 1, 2, or 3.\n")
# ---------- Input to set number of image samples ----------

# ---------- Process image using Gaussian Filter ----------
def process_gaussian_filter(args):
    image_directory, image_file, output_directory = args
    image_path = os.path.join(image_directory, image_file)
    image = cv2.imread(image_path)

    if image is None:
        print(f"Could not open or find the image: {image_path}")
        return

    # Record the start time
    start_time = time.time()

    # Apply Gaussian blur
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
    # Resize the Gaussian image for display
    resized_gaussian_image = cv2.resize(blurred_image_output, (desired_width, int(blurred_image_output.shape[0] * (desired_width / blurred_image_output.shape[1]))))

    # Record the end time
    end_time = time.time()
    # Calculate the total time
    each_total_time = end_time - start_time

    # Output time taken for each image
    print(f"[{image_file}] Total time taken: {each_total_time:.4f} seconds")

    # Save the blurred image to the output directory
    output_path = os.path.join(output_directory, f"gaussianblur_{image_file}")
    cv2.imwrite(output_path, resized_gaussian_image)

# ---------- Process image using Gaussian Filter ----------


# ---------- Process image using Bilateral Filter ----------
def gaussian(x,sigma):
    return (1.0/(2*np.pi*(sigma**2)))*np.exp(-(x**2)/(2*(sigma**2)))

def distance(x1,y1,x2,y2):
    return np.sqrt(np.abs((x1-x2)**2-(y1-y2)**2))

def process_bilateral_filter(args):

    image_directory, image_file, output_directory = args
    image_path = os.path.join(image_directory, image_file)
    image = cv2.imread(image_path)

    if image is None:
        print(f"Could not open or find the image: {image_path}")
        return

    # Record the start time
    start_time = time.time()

    # Apply bilateral filter
    diameter = 9     # Diameter of each pixel neighborhood to consider
    sigma_i = 75     # Intensity similarity weight
    sigma_s = 75     # Spatial distance weight
    blurred_image_output = cv2.bilateralFilter(image, diameter, sigma_i, sigma_s)

    # Resize parameters
    desired_width = 500

    # Resize the original image for display
    resized_image = cv2.resize(image, (desired_width, int(image.shape[0] * (desired_width / image.shape[1]))))
    # Resize the bilateral image for display
    resized_bilateral_image = cv2.resize(blurred_image_output, (desired_width, int(blurred_image_output.shape[0] * (desired_width / blurred_image_output.shape[1]))))

    # Record the end time
    end_time = time.time()
    # Calculate the total time
    each_total_time = end_time - start_time

    # Output time taken for each image
    print(f"[{image_file}] Total time taken: {each_total_time:.4f} seconds")

    # Save the blurred image to the output directory
    output_path = os.path.join(output_directory, f"bilateral_{image_file}")
    cv2.imwrite(output_path, resized_bilateral_image)

# ---------- Process image using Bilateral Filter ----------


# ---------- Gaussian filter run with multiprocessing ----------
def multiprocessing_gaussian_filter(image_directory, image_files, num_image, num_process):
    start = time.perf_counter()

    # Specify the paths for the output gaussian and bilateral output directories 
    gaussian_output_directory = os.path.join(image_directory, "gaussian_filter_image")

    # Create a list of arguments for the gaussian multiprocessing pool
    gaussian_args_list = [(image_directory, image_file, gaussian_output_directory) for image_file in image_files]

    # Create the gaussian output directory if it doesn't exist
    if not os.path.exists(gaussian_output_directory):
        os.makedirs(gaussian_output_directory)

    # Create a multiprocessing pool
    pool = Pool(processes=num_process)  # Adjust the number of processes as needed

    # Apply Gaussian blur to each image in parallel
    pool.map(process_gaussian_filter, gaussian_args_list)

    # Close the pool to release resources
    pool.close()
    pool.join()

    print("All images have been processed.")

    finish = time.perf_counter()
    total_time = finish - start

    # Multi-Processing Output Result
    print("\n---------- Multi-Processing Result ----------")
    print(f"Total time taken for running {num_image} images using gaussian filter in {num_process} processing: {total_time:.4f} seconds\n")
# ---------- Gaussian filter run with multiprocessing ----------


# ---------- Bilateral filter run with multiprocessing ----------
def multiprocessing_bilateral_filter(image_directory, image_files, num_image, num_process):
    start = time.perf_counter()

    # Specify the paths for the output gaussian and bilateral output directories 
    bilateral_output_directory = os.path.join(image_directory, "bilateral_filter_image")

    # Create the gaussian output directory if it doesn't exist
    if not os.path.exists(bilateral_output_directory):
        os.makedirs(bilateral_output_directory)

    # Create a list of arguments for the bilateral multiprocessing pool
    bilateral_args_list = [(image_directory, image_file, bilateral_output_directory) for image_file in image_files]

    # Create a multiprocessing pool
    pool = Pool(processes=num_process)  # Adjust the number of processes as needed

    # Apply Bilateral Filter to each image in parallel
    pool.map(process_bilateral_filter, bilateral_args_list)

    # Close the pool to release resources
    pool.close()
    pool.join()

    print(num_image + " images have been processed.")

    finish = time.perf_counter()
    total_time = finish - start

    # Multi-Processing Output Result
    print("\n---------- Multi-Processing Result ----------")
    print(f"Total time taken for running {num_image} images using bilateral filter in {num_process} processing: {total_time:.4f} seconds\n")
# ---------- Bilateral filter run with multiprocessing ----------

def input_processes():
    # Choose to run Gaussian or Bilateral filters
    while True:
        print("Choose an option:")
        print("1. Number of 2 processes")
        print("2. Number of 4 processes")
        print("3. Number of 8 processes")

        num_process = input("Enter your choice (1/2/3): ")

        if num_process in ["1", "2", "3"]:
            # Convert the user input to an integer
            choice = int(num_process)

            if choice == 1:
                print("\nRun 2 number of processes\n")
                return 2    
            elif choice == 2:
                print("\nRun 4 number of processes\n")
                return 4 
            elif choice == 3:
                print("\nRun 8 number of processes\n")
                return 8 

            # Exit the loop once a valid choice is made
            break
        else:
            print("Invalid choice. Please enter 1, 2, 3.\n")

def main():

    print("\n*************** Multi-Processing ***************\n")

    # Get the directory of the current script
    script_directory = os.path.dirname(os.path.abspath(__file__))

    # Input to set the number of images
    num_image = input_image_sample()

    # Input to set the number of process
    num_process = input_processes()

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
                print("\nRun " + num_image + " images using Gaussian Filter in multi-processing\n")
                multiprocessing_gaussian_filter(image_directory, image_files, num_image, num_process)
            elif choice == 2:
                print("\nRun " + num_image + " images using Bilateral Filter in multi-processing\n")
                multiprocessing_bilateral_filter(image_directory, image_files, num_image, num_process)

            # Exit the loop once a valid choice is made
            break
        else:
            print("Invalid choice. Please enter 1, 2.\n")


if __name__ == "__main__":
    main()

