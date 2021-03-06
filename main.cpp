#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

int main (int argc, char* argv[])
{
  std::string file_name;
  
  std::cout << "Specify path to image (with extension): ";
  std::cin >> file_name;

  int width;
  int height;
  int n;

  unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &n, 3);

  if (data == nullptr)
  {
    stbi_image_free(data); // Just to be safe.
    
    std::cout << "Error reading file!\n";
    std::cin.get();
    exit(1);
  }
    
  const int newWidth = 100;
  const int newHeight = (((double)height / width) * newWidth);
  
  // Allocate memory based on (width * height * num_of_channels) char is 1 byte so no need for sizeof()
  unsigned char* resized_image = (unsigned char*)::operator new(newWidth * newHeight * 3);                   
  const char ASCII[11] = { '@', '#', '$', '%', '?', 
                           '*', '+', ';', ':', ',', '.' };
  
  // Resize image
  stbir_resize_uint8(data, width, height, 0,
                     resized_image, newWidth, newHeight, 0, 3);
  
  stbi_image_free(data); // Original no longer needed.
                    
  for (int i = 0; i < newHeight; ++i)
  {
    for (int j = 0; j < newWidth; ++j)
    {
      const size_t INDEX = 3 * (i * newWidth + j);
      const int pixel_grayscale_value = (static_cast<int>(resized_image[INDEX]) + 
                                   static_cast<int>(resized_image[INDEX + 1]) +
                                   static_cast<int>(resized_image[INDEX + 2])) / 3;

      std::cout << ASCII[pixel_grayscale_value / 25];
    }

    std::cout << '\n';
  }

  ::operator delete(resized_image, newWidth * newHeight * 3);
  
  system("pause");
  return 0;
}