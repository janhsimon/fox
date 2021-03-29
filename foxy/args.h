enum output
{
  OUTPUT_EXECUTABLE,
  OUTPUT_INTEL_X64_ASM
};

enum target_platform
{
  TARGET_PLATFORM_LINUX,
  TARGET_PLATFORM_WIN
};

enum output get_output();
enum target_platform get_target_platform();

char parse_options(int argc, char *argv[]);