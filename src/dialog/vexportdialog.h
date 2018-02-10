#ifndef VEXPORTDIALOG_H
#define VEXPORTDIALOG_H

#include <QDialog>
#include <QPageLayout>

#include "vconstants.h"

class QLabel;
class VLineEdit;
class QDialogButtonBox;
class QComboBox;
class QPushButton;
class QGroupBox;
class QPlainTextEdit;
class VNotebook;
class VDirectory;
class VFile;
class VCart;
class VExporter;


enum class ExportSource
{
    CurrentNote = 0,
    CurrentDirectory,
    CurrentNotebook,
    Cart
};


enum class ExportFormat
{
    Markdown = 0,
    HTML,
    PDF
};


struct ExportOption
{
    ExportOption(ExportSource p_source,
                 ExportFormat p_format,
                 MarkdownConverterType p_renderer,
                 QPageLayout *p_layout)
        : m_source(p_source),
          m_format(p_format),
          m_renderer(p_renderer),
          m_layout(p_layout)
    {
    }

    ExportSource m_source;
    ExportFormat m_format;
    MarkdownConverterType m_renderer;
    QPageLayout *m_layout;
};


class VExportDialog : public QDialog
{
    Q_OBJECT
public:
    VExportDialog(VNotebook *p_notebook,
                  VDirectory *p_directory,
                  VFile *p_file,
                  VCart *p_cart,
                  MarkdownConverterType p_renderer,
                  QWidget *p_parent = nullptr);

private slots:
    void startExport();

    void handleBrowseBtnClicked();

    void handleInputChanged();

    void handleLayoutBtnClicked();

    void handleCurrentFormatChanged(int p_index);

private:
    void setupUI();

    QWidget *setupPDFAdvancedSettings();

    void initUIFields(MarkdownConverterType p_renderer);

    QString getOutputDirectory() const;

    void appendLogLine(const QString &p_text);

    // Return number of files exported.
    int doExport(VFile *p_file,
                 const ExportOption &p_opt,
                 const QString &p_outputFolder,
                 QString *p_errMsg = NULL);

    int doExport(VDirectory *p_directory,
                 const ExportOption &p_opt,
                 const QString &p_outputFolder,
                 QString *p_errMsg = NULL);

    int doExport(VNotebook *p_notebook,
                 const ExportOption &p_opt,
                 const QString &p_outputFolder,
                 QString *p_errMsg = NULL);

    int doExport(VCart *p_cart,
                 const ExportOption &p_opt,
                 const QString &p_outputFolder,
                 QString *p_errMsg = NULL);

    int doExportMarkdown(VFile *p_file,
                         const ExportOption &p_opt,
                         const QString &p_outputFolder,
                         QString *p_errMsg = NULL);

    int doExportPDF(VFile *p_file,
                    const ExportOption &p_opt,
                    const QString &p_outputFolder,
                    QString *p_errMsg = NULL);

    // Return false if we could not continue.
    bool checkUserAction();

    void updatePageLayoutLabel();

    QComboBox *m_srcCB;

    QComboBox *m_formatCB;

    QComboBox *m_rendererCB;

    VLineEdit *m_outputEdit;

    QPushButton *m_browseBtn;

    QGroupBox *m_basicBox;

    QGroupBox *m_settingBox;

    QWidget *m_pdfSettings;

    QPlainTextEdit *m_consoleEdit;

    QDialogButtonBox *m_btnBox;

    QPushButton *m_openBtn;

    QPushButton *m_exportBtn;

    QLabel *m_layoutLabel;

    QPushButton *m_layoutBtn;

    VNotebook *m_notebook;

    VDirectory *m_directory;

    VFile *m_file;

    VCart *m_cart;

    QPageLayout m_pageLayout;

    // Whether we are exporting files.
    bool m_inExport;

    // Asked to stop exporting by user.
    bool m_askedToStop;

    // Exporter used to export PDF and HTML.
    VExporter *m_exporter;

    // Last output folder path.
    static QString s_lastOutputFolder;
};

#endif // VEXPORTDIALOG_H
