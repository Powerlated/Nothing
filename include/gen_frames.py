# ffmpeg -i rickroll.mp4 -vf "scale=480:240:force_original_aspect_ratio=decrease,pad=480:240:-1:-1:color=black" %d.jpg

frames = 300

f = open("frames.h", "w")
f.write(f"#define FRAME_COUNT {frames}\n")
f.write("#include \"incbin.h\"\n")
for x in range(1, frames + 1):
    f.write(f"INCBIN(F{x}, \"frames/{x}.jpg\");\n")

f.write("const unsigned char* const frames[] = {")
for x in range(1, frames + 1):
    f.write(f"gF{x}Data,\n")
f.write("};")

f.write("const unsigned int frameSizes[] = {")
for x in range(1, frames + 1):
    f.write(f"gF{x}Size,\n")
f.write("};")



