#include <gio/gio.h>
#include <glib.h>
 
int
main (int   argc,
      char *argv[])
{
     
    GFile            *file;/* 文件抽象数据类型 */
    GOutputStream    *fos; /* 用来写的 */
    GError           *error = NULL;
     
    /* 创建file对象 */
    file = g_file_new_for_path ("./test_file");
     
    /* 获取输出流 */
    fos = G_OUTPUT_STREAM (g_file_replace (file, NULL, FALSE, 
                                           G_FILE_CREATE_NONE,
                                           NULL, &error));
    if (!fos)
    {
        g_error ("%s", error->message);
        g_error_free (error);
        return 1;
    }
     
    /* 写入 */
    GString *str = g_string_new ("这些文字将写入 test_file。\n");
    g_output_stream_write_all (fos, str->str, str->len, NULL, NULL, NULL);
    g_output_stream_flush (fos, NULL, NULL);
    g_string_free (str, TRUE);
     
    /* 清理 */
    g_output_stream_close (fos, NULL, NULL);
    g_object_unref (file);
    return 0;
}
