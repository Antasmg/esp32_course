#include <stdio.h>

void app_main(void)
{
  extern const unsigned char indexHtml[] asm("_binary_index_html_start");
  printf("html = %s\n", indexHtml);

  extern const unsigned char sample[] asm("_binary_text_file_txt_start");
  printf("sample = %s\n", sample);

  extern const unsigned char imgStart[] asm("_binary_pinout_jpeg_start");
  extern const unsigned char imgEnd[] asm("_binary_pinout_jpeg_end");
  const unsigned int imgSize = imgEnd - imgStart;
  printf("img size is %d\n", imgSize);

}