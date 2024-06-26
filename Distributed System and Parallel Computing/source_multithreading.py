import cv2
import numpy as np
import os
import time
import threading
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
def process_gaussian_filter(start_index, end_index, image_directory, image_files, num_image):

    # Specify the paths for the gaussian output directories 
    gaussian_output_directory = os.path.join(image_directory, "gaussian_filter_image")

    # Create the gaussian output directory if it doesn't exist
    if not os.path.exists(gaussian_output_directory):
        os.makedirs(gaussian_output_directory)

    for i in range(start_index, end_index):
        image_file = image_files[i]
        image_path = os.path.join(image_directory, image_file)
        image = cv2.imread(image_path)

        if image is None:
            print(f"Could not open or find the image: {image_path}")
            continue

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
        print(f"{i + 1} - [{image_file}] Total time taken: {each_total_time:.4f} seconds")

        # Save the blurred image to the output directory
        output_path = os.path.join(gaussian_output_directory, f"gaussianblur_{image_file}")
        cv2.imwrite(output_path, resized_gaussian_image)

# ---------- Process image using Gaussian Filter ----------


# ---------- Process image using Bilateral Filter ----------
def gaussian(x,sigma):
    return (1.0/(2*np.pi*(sigma**2)))*np.exp(-(x**2)/(2*(sigma**2)))

def distance(x1,y1,x2,y2):
    return np.sqrt(np.abs((x1-x2)**2-(y1-y2)**2))

def process_bilateral_filter(start_index, end_index, image_directory, image_files, num_image):

    # Specify the paths for the bilateral output directories 
    bilateral_output_directory = os.path.join(image_directory, "bilateral_filter_image")

    # Create the bilateral output directory if it doesn't exist
    if not os.path.exists(bilateral_output_directory):
        os.makedirs(bilateral_output_directory)

    for i in range(start_index, end_index):
        image_file = image_files[i]
        image_path = os.path.join(image_directory, image_file)
        image = cv2.imread(image_path)

        if image is None:
            print(f"Could not open or find the image: {image_path}")
            continue

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
        print(f"{i + 1} - [{image_file}] Total time taken: {each_total_time:.4f} seconds")

        # Save the blurred image to the output directory
        output_path = os.path.join(bilateral_output_directory, f"bilateral_{image_file}")
        cv2.imwrite(output_path, resized_bilateral_image)

# ---------- Process image using Bilateral Filter ----------


# ---------- Input to set number of THREADS ----------
def input_number_threads():
    while True:
        input_threads = input("Enter the number of threads between 1 - 16: ")

        try:
            choice = int(input_threads)
            if 1 <= choice <= 16:
                print("\nNumber of threads: " + str(choice) + "\n")
                return choice
                break
            else:
                print("Invalid input. Please enter a number between 1 and 16.\n")
        except ValueError:
            print("Invalid input. Please enter a valid number.\n")
# ---------- Input to set number of THREADS ----------


# ---------- Gaussian filter run with multithreading ----------

def threading_gaussian_filter(image_directory, image_files, num_image, num_threads):
    
    # Record the start time
    total_start_time = time.time()

    # Calculate the number of images to process in each thread
    images_per_thread = len(image_files) // num_threads

    threads = []
    for i in range(num_threads):
        start_index = i * images_per_thread
        end_index = min((i + 1) * images_per_thread, len(image_files))
        thread = threading.Thread(target=process_gaussian_filter, args=(start_index, end_index, image_directory, image_files, num_image))
        threads.append(thread)

    # Start the threads
    for thread in threads:
        thread.start()

    # Wait for all threads to finish
    for thread in threads:
        thread.join()

    print("All threads have finished processing.")

    # Record the end time
    total_end_time = time.time()

    # Calculate the total time
    total_time = total_end_time - total_start_time

    # Multi-Threading Output Result
    print("\n---------- Multi-Threading Result ----------")
    print(f"Total time taken for running {num_image} images using gaussian filter in {num_threads} threads: {total_time:.4f} seconds\n")

# ---------- Gaussian filter run with multithreading ----------


# ---------- Bilateral filter run with multithreading ----------
def threading_bilateral_filter(image_directory, image_files, num_image, num_threads):

    # Record the start time
    total_start_time = time.time()

    # Calculate the number of images to process in each thread
    images_per_thread = len(image_files) // num_threads

    threads = []
    for i in range(num_threads):
        start_index = i * images_per_thread
        end_index = min((i + 1) * images_per_thread, len(image_files))
        thread = threading.Thread(target=process_bilateral_filter, args=(start_index, end_index, image_directory, image_files, num_image))
        threads.append(thread)

    # Start the threads
    for thread in threads:
        thread.start()

    # Wait for all threads to finish
    for thread in threads:
        thread.join()

    print("All threads have finished processing.")

    # Record the end time
    total_end_time = time.time()

    # Calculate the total time
    total_time = total_end_time - total_start_time

    # Multi-Threading Output Result
    print("\n---------- Multi-Threading Result ----------")
    print(f"Total time taken for running {num_image} images using bilateral filter in {num_threads} threads: {total_time:.4f} seconds\n")

# ---------- Bilateral filter run with multithreading ----------


def main():

    print("\n*************** Multi-Threading ***************\n")

    # Get the directory of the current script
    script_directory = os.path.dirname(os.path.abspath(__file__))

    num_image = input_image_sample()

    # Directory containing the original images
    image_directory = os.path.join(script_directory, "dataset", num_image + "_images") # Run for 100 images

    # Define the number of threads
    num_threads = input_number_threads()

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

            gaussian_num_threads = num_threads
            bilateral_num_threads = num_threads

            if choice == 1:
                print("\nRun " + num_image + " images using Gaussian Filter in " + str(gaussian_num_threads) + " threads\n")
                threading_gaussian_filter(image_directory, image_files, num_image, num_threads)     
            elif choice == 2:
                print("\nRun " + num_image + " images using Bilateral Filter in " + str(bilateral_num_threads) + " threads\n")
                threading_bilateral_filter(image_directory, image_files, num_image, num_threads)

            # Exit the loop once a valid choice is made
            break
        else:
            print("Invalid choice. Please enter 1, 2.\n")

if __name__ == "__main__":
    main()


