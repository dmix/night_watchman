#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>

static const char *config_file = "settings.cfg";
config_t cfg;

int read_config_file()
{
    config_init(&cfg);

    if (!config_read_file(&cfg, config_file)) {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
        config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return(EXIT_FAILURE);
    }

    const char *setting_config_path;
    config_lookup_string(&cfg, "config_file", &setting_config_path);
    printf("config: %s\n", setting_config_path);
    extern char *config_path;
    config_path = (char *)setting_config_path;

    return(EXIT_SUCCESS);
}

int write_config_file(char *config_setting)
{
    config_setting_t *root, *setting;
    root = config_root_setting(&cfg);
    setting = config_setting_get_member(root, "config_file");
    if(!setting)
        setting = config_setting_add(root, "config_file", CONFIG_TYPE_STRING);

    config_setting_set_string(setting, config_setting);

    /* Write out the updated configuration. */
    if(! config_write_file(&cfg, config_file)) {
        fprintf(stderr, "Error while writing file.\n");
        config_destroy(&cfg);
        return(EXIT_FAILURE);
    }

    fprintf(stderr, "Updated configuration successfully written to: %s\n",
            config_file);

    //config_destroy(&cfg);
    return(EXIT_SUCCESS);
}
