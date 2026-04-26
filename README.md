# miniRT

> A 42 School graphics project — a ray tracer in C rendering 3D scenes from a custom scene description file.

---

## 📋 Overview

**miniRT** is a ray tracer built from scratch in C using the **MiniLibX** library. It reads a `.rt` scene file describing geometric objects, lights, and camera settings, then renders the scene by casting rays and computing intersections, lighting, and colors.

---

## 📁 File Structure

```
miniRT/
├── Makefile
├── includes/
│   └── miniRT.h
├── libft/
├── mlx-linux/
├── scenes/
│   ├── basic_1.rt
│   ├── basic_2.rt
│   ├── basic_3.rt
│   ├── brighteness_1.rt
│   ├── brighteness_2.rt
│   ├── brighteness_3.rt
│   ├── camera_1.rt
│   ├── camera_2.rt
│   ├── camera_3.rt
│   ├── camera_4.rt
│   ├── colored_light.rt
│   ├── columns.rt
│   ├── cylinders.rt
│   ├── rotation_test_1.rt
│   ├── rotation_test_2.rt
│   ├── spheres.rt
│   ├── translation_test.rt
│   └── error/
│       ├── 2_amb.rt
│       ├── 2_camera.rt
│       ├── color_amb.rt
│       ├── no_amb.rt
│       ├── no_camera.rt
│       ├── no_light.rt
│       ├── punct_error.rt
│       ├── tokens_amb.rt
│       └── vector_error.rt
└── srcs/
    ├── main.c
    ├── parsing/
    │   ├── parser.c
    │   ├── parse_objs.c
    │   ├── parse_light.c
    │   ├── parse_utils.c
    │   └── parse_utils_2.c
    ├── rt/
    │   ├── ray.c
    │   ├── hit.c
    │   ├── hit_cylinder.c
    │   └── light.c
    └── utils/
        ├── color.c
        ├── exit.c
        ├── free.c
        ├── mlx_utils.c
        ├── numbers.c
        ├── obj_utils.c
        ├── ray_utils.c
        ├── vector.c
        ├── vector2.c
        └── vector3.c
```

### Directory breakdown

| Directory | Role |
|-----------|------|
| `includes/` | Shared header file |
| `srcs/parsing/` | Scene file parsing and validation |
| `srcs/rt/` | Ray casting, intersection computation, and lighting |
| `srcs/utils/` | Colors, vectors, memory management, MLX utilities |
| `scenes/` | Sample `.rt` scene files for testing |
| `scenes/error/` | Invalid scene files for error handling tests |
| `libft/` | Personal C library |
| `mlx-linux/` | MiniLibX graphics library |

---

## 🎨 Scene File Format (`.rt`)

A `.rt` file describes the scene with one element per line:

| Identifier | Element |
|------------|---------|
| `A` | Ambient lighting |
| `C` | Camera |
| `L` | Light source |
| `sp` | Sphere |
| `pl` | Plane |
| `cy` | Cylinder |

### Example
```
A  0.2  255,255,255
C  0,0,-5  0,0,1  70
L  -40,50,0  0.6  255,255,255
sp  0,0,5  1.5  255,0,0
pl  0,-1,0  0,1,0  100,200,100
cy  0,1,0  0,1,0  1  3  0,0,255
```

---

## 🔧 Usage

```bash
# Compile
make

# Run with a scene file
./miniRT scenes/basic_1.rt
```

---

*42 Paris — miniRT (group project)*
