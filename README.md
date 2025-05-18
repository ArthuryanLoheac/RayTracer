# Raytracer

## Description

A c++ implementation of a raytracing program using scene in libconfig++ configuration file.

## Usage

```bash
./raytracer <SCENE_FILE> [-r]

  SCENE_FILE: scene configuration
  -r: run in no window mode
```

## Configuration

`cong.cfg`
```
# This is the configuration file for the raytracer program.
raytracer : {
    # Configuration of the camera
    @include "camera.cfg"

    # Configuration of the primitives
    @include "primitives.cfg"

    # Configuration of the light sources
    @include "lights.cfg"
};
```

`camera.cfg`
```
# Configuration of the camera
camera : {
    resolution : {
        width = (int)[0 - 8000];
        height = (int)[0 - 8000];
    };
    position : {
        x = (float)0.0;
        y = (float)0.0;
        z = (float)0.0;
    };
    rotation : {
        x = (float)0.0;
        y = (float)0.0;
        z = (float)0.0;
    };
    fov = (float)90.0;
    skybox = (string)"path";
};
```

`primitives.cfg`
```
# Configuration of the primitives
primitives = (
    {
        type = (string)"type";
        position : {
            x = (float)0.0;
            y = (float)0.0;
            z = (float)0.0;
        };
        rotation : {
            x = (float)0.0;
            y = (float)0.0;
            z = (float)0.0;
        };
        scale : {
            x = (float)0.0;
            y = (float)0.0;
            z = (float)0.0;
        };
        material : {
            type = (string)"type"
            color : {
                r = (int)0;
                g = (int)0;
                b = (int)0;
            };
            color1 : {
                r = (int)0;
                g = (int)0;
                b = (int)0;
            };
            color2 : {
                r = (int)0;
                g = (int)0;
                b = (int)0;
            };
            rotation : {
            x = (float)0.0;
            y = (float)0.0;
            z = (float)0.0;
            };
            scale : {
                x = (float)0.0;
                y = (float)0.0;
                z = (float)0.0;
            };
            path = (string)"path"
            octave = (int)0;
            shininess = (float)0.0;
            specular = (float)0.0;
        };
        radius = (float)1.5;
        angle = (float)0.0;
        heigth = (float)0.0;
        filename = (string)"path";
        children = (
          {
          }
        );
    }
);
```

`lights.cfg`
```
# Configuration of the light sources
lights : {
    ambient = (
        {
            color : {
                r = (int)0;
                g = (int)0;
                b = (int)0;
            };
            position : {
                x = (float)0.0;
                y = (float)0.0;
                z = (float)0.0;
            };
            rotation : {
                x = (float)0.0;
                y = (float)0.0;
                z = (float)0.0;
            };
            scale : {
                x = (float)0.0;
                y = (float)0.0;
                z = (float)0.0;
            };
            angle = (float)0.0;
            intensity = (float)1.0;
        }
    );

    spot = (
    );
};
```