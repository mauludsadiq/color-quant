use std::env;
use std::error::Error;

use color_quant_k::QuantizerK;
use image::{GenericImageView, ImageBuffer, Rgb};

fn main() -> Result<(), Box<dyn Error>> {
    let args: Vec<String> = env::args().collect();
    if args.len() != 3 {
        eprintln!("Usage: quantize_image_k5 <input.png/jpg> <output.png>");
        std::process::exit(1);
    }

    let input_path = &args[1];
    let output_path = &args[2];

    let img = image::open(input_path)?;
    let rgb_img = img.to_rgb8();
    let (width, height) = rgb_img.dimensions();

    let q = QuantizerK::new(5);

    let mut out_img: ImageBuffer<Rgb<u8>, Vec<u8>> =
        ImageBuffer::new(width, height);

    for (x, y, pixel) in rgb_img.enumerate_pixels() {
        let rgb_f = [
            pixel[0] as f32 / 255.0,
            pixel[1] as f32 / 255.0,
            pixel[2] as f32 / 255.0,
        ];

        let proj = q.project_rgb(rgb_f);

        let r = (proj[0].clamp(0.0, 1.0) * 255.0 + 0.5) as u8;
        let g = (proj[1].clamp(0.0, 1.0) * 255.0 + 0.5) as u8;
        let b = (proj[2].clamp(0.0, 1.0) * 255.0 + 0.5) as u8;

        out_img.put_pixel(x, y, Rgb([r, g, b]));
    }

    out_img.save(output_path)?;

    println!(
        "Wrote K=5 quantized image {}x{} to {}",
        width, height, output_path
    );

    Ok(())
}
