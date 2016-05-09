#include <stdlib.h>
#include "common.h"
#include "raytracer.h"
#include "scene.h"
#include "surface.h"
#include "common/cpu_bitmap.h"

#define SCRWIDTH	800
#define SCRHEIGHT	600


Raytracer::Surface* surface = 0;
Pixel* buffer = 0;
Raytracer::Engine* tracer = 0;

int main(int argc, char* argv[])
{
	CPUBitmap *bitmap = new CPUBitmap(SCRWIDTH, SCRHEIGHT, buffer);
	
	surface = new Raytracer::Surface(SCRWIDTH, SCRHEIGHT);
	buffer = surface->GetBuffer();
	surface->Clear(0);
	surface->InitCharset();

	// prepare renderer
	tracer = new Raytracer::Engine();
	tracer->GetScene()->InitScene();
	tracer->SetTarget(surface->GetBuffer(), SCRWIDTH, SCRHEIGHT);
	tracer->InitRender();
	// while (!tracer->RenderTiles()) DrawWindow();
	tracer->Render();

	memcpy(bitmap->get_ptr(), buffer, SCRWIDTH*SCRHEIGHT * 3 * sizeof(char));
	//while (!tracer->Render())
	bitmap->display_and_exit();
	
	if (bitmap)
		delete bitmap;
}
