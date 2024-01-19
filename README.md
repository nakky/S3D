# S3D

S3D is a portable 3d game library, available for Windows, macOS, Linux.

## How to build

### Meson

S3D uses meson as the build system.
In order to use the new version, it is recommended to install with pip.

```
$ pip3 install meson
$ pip3 install ninja
```

### Meson - build

You can run the build command in the S3D root folder.

```
$ meson build
$ ninja -C build
```

### Meson - subdir

Download it as a submodule in your project.

```
Project
├─ modules/
│  └─ S3D/
│     └─ meson.build
└─meson.build
```

Call in subdir for the "src" folder in your project's meson.build.

```
subdir('modules/S3D/src')
```

Variable ”s3d_lib” can be used for linking.

```
s3d_dep = declare_dependency(link_with: s3d_lib)
...
deps = [
  s3d_dep,
...
}
executable(
...
  dependencies: deps,
...
)
```

Run the following command in the root folder of the project.

```
$ meson build
$ ninja -C build
```
