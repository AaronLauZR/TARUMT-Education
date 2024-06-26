sing Gaussian Filter\n")
                multiprocessing_bilateral_filter()
            elif choice == 2:
                print("\nRun " + num_image + " images using Bilateral Filter\n")
                multiprocessing_gaussian_filter()

            # Exit the loop once a valid choice is made
            break
        else:
            print("Invalid choice. Please enter 1, 2.\n")


if __name__ == "__main__":
    main()

