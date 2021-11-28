#include <cstdint>
#include <cstddef>
#include <cstdio>
#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include "font.hpp"

using namespace std;

void* operator new(size_t size, void* buf)
{
  return buf;
}

void	operator delete(void *obj) noexcept{}

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

extern "C" void	KernelMain(const FrameBufferConfig &frame_buffer_config)
{
	int			x;
	int			y;

	switch(frame_buffer_config.pixel_format)
	{
		case	kPixelRGBResv8BitPerColor:
				pixel_writer = new(pixel_writer_buf)RGBResv8BitPerColorPixelWriter(frame_buffer_config);
				break;
		case	kPixelBGRResv8BitPerColor:
				pixel_writer = new(pixel_writer_buf)BGRResv8BitPerColorPixelWriter(frame_buffer_config);
				break;
	}
	for(x = 0; x < frame_buffer_config.horizontal_resolution; x++)
	{
		for(y = 0; y < frame_buffer_config.vertical_resolution; y++)
			pixel_writer->Write(x, y, {255, 255, 255});
	}
	for(x = frame_buffer_config.horizontal_resolution / 4; x < frame_buffer_config.horizontal_resolution * 3 / 4; x++)
	{
		for(y = frame_buffer_config.vertical_resolution / 4; y < frame_buffer_config.vertical_resolution * 3 / 4; y++)
			pixel_writer->Write(x, y, {0, 255, 0});
	}
	WriteString(*pixel_writer, 0, 66, "Hello, world!\n", {0, 0, 255});
	char	buf[128];
	sprintf(buf, "1 + 2 = %d", 1+ 2);
	WriteString(*pixel_writer, 0, 82, buf, {0, 0, 0});
	while(1) __asm__("hlt");
}
