using System.Windows;
using System.Windows.Controls;

namespace SNEditor.GameProject
{
    /// <summary>
    /// Interaction logic for OpenProjectView.xaml
    /// </summary>
    public partial class OpenProjectView : UserControl
    {
        public OpenProjectView()
        {
            InitializeComponent();

            // FOCUS FIRST ITEM IN PROJECT LIST
            Loaded += (s, e) =>
            {
                var item = projectsListBox.ItemContainerGenerator
                .ContainerFromIndex(projectsListBox.SelectedIndex) as ListBoxItem;
                item?.Focus();
            };
        }
        // OPEN PROJECT CALL
        private void OnOpen_Button_Click(object sender, RoutedEventArgs e)
        {
            OpenSelectedProject();
        }
        // DOUBLE CLICK TO OPEN PROJECT
        private void OnListBoxItem_Mouse_DoubleClick(object sender, RoutedEventArgs e)
        {
            OpenSelectedProject();
        }

        // OPEN PROJECT + CLOSE PROJECT BROWSER
        private void OpenSelectedProject()
        {
            var project = OpenProject.Open(projectsListBox.SelectedItem as ProjectData);
            bool dialogResult = false;
            var win = Window.GetWindow(this);
            if (project != null)
            {
                dialogResult = true;
                win.DataContext = project;
            }
            win.DialogResult = dialogResult;
            win.Close();
        }
    }
}
