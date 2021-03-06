#include <cstdint>
#include <cstddef>
#include "header.hpp"
#include <cstdint>
#include <cstddef>

using namespace std;

struct PixelColor {
  uint8_t r, g, b;
};

class PixelWriter
{
	public:
		PixelWriter(const FrameBufferConfig &config) : config_{config}{}
		virtual ~PixelWriter(){};
		virtual void	Write(int x, int y, const PixelColor &c) = 0;
	protected:
		uint8_t	*PixelAt(int x, int y)
		{
			return (config_.frame_buffer + 4 * (config_.pixels_per_scan_line * y + x));
		}
	private:
		const FrameBufferConfig	&config_;
};

class	RGBResv8BitPerColorPixelWriter : public PixelWriter
{
	public:
		using PixelWriter::PixelWriter;

	virtual void	Write(int x, int y, const PixelColor &c) override
	{
		auto p = PixelAt(x, y);
		p[0] = c.r;
		p[1] = c.g;
		p[2] = c.b;
	}
};

class	BGRResv8BitPerColorPixelWriter : public PixelWriter
{
	public:
		using	PixelWriter::PixelWriter;

	virtual void	Write(int x, int y, const PixelColor &c) override
	{
		auto p = PixelAt(x, y);
		p[0] = c.b;
		p[1] = c.g;
		p[2] = c.r;
	}
};

void* operator new(size_t size, void* buf)
{
  return buf;
}

void	operator delete(void *obj) noexcept{}

char		pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter	*pixel_writer;

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
	while(1) __asm__("hlt");
}
