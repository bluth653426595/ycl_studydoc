#include <gio/gio.h>
#include <glib.h>

int main (int   argc,
      char *argv[])
{
    if (argc < 2)
        return 1;

    GFile            *file;/* 文件抽象数据类型 */
    GInputStream     *fis; /* 用来读的 */
    GError           *error = NULL;
    GDataInputStream *dis; /* 抽象输入流 */
    /* 创建file对象 */
    file = g_file_new_for_path (argv[1]);

    /* 获取输入流 */
    fis = G_INPUT_STREAM (g_file_read (file, NULL, &error));
    if (!fis)
    {
        g_error ("%s", error->message);
        g_error_free (error);
        return 1;
    }

    /* 读取 */
    dis = g_data_input_stream_new (fis);
    char *line;
    while (TRUE)
    {
        line = g_data_input_stream_read_line (dis, NULL, NULL, &error);
        if (error)
        {
            g_error ("%s", error->message);
            return 1;
        }
        if (!line)
            break;

        g_print ("%s\n", line);
        g_free (line);
    }

    /* 清理 */
    g_input_stream_close (fis, NULL, NULL);
    g_object_unref (file);
    return 0;
}
