from PIL import Image
import os

def create_gif(image_folder, output_path, duration):
    # Get all image files in the folder
    images = []
    for file_name in sorted(os.listdir(image_folder)):
        if file_name.lower().endswith(('.png', '.jpg', '.jpeg')):
            image_path = os.path.join(image_folder, file_name)
            img = Image.open(image_path)
            images.append(img)

    if not images:
        print("No valid image files found in folder.")
        return

    # Save as GIF
    images[0].save(
        output_path,
        save_all=True,
        append_images=images[1:],
        duration=duration,
        loop=0
    )
    print(f"GIF saved at: {output_path}")

# ----- CHANGE THESE VALUES -----
image_folder = "images"              # Folder where your images are
output_path = "output.gif"           # Output GIF name
duration = 500                       # Time per frame in milliseconds
# --------------------------------

create_gif(image_folder, output_path, duration)