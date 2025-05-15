    public Form1()
    {
        InitializeComponents();
        points = new DataPointCollection();
    }

    private void InitializeComponents()
    {
        this.MinimumSize = new Size(800, 600);
        this.Text = "Function Tabulation";

        // Initialize input controls
        txtXMin = CreateTextBox("txtXMin", new Point(20, 20), new Size(100, 20));
        txtXMax = CreateTextBox("txtXMax", new Point(20, 50), new Size(100, 20));
        txtA = CreateTextBox("txtA", new Point(20, 80), new Size(100, 20));
        txtB = CreateTextBox("txtB", new Point(20, 110), new Size(100, 20));
        txtC = CreateTextBox("txtC", new Point(20, 140), new Size(100, 20));

        // Set default values for variant 1
        txtXMin.Text = "1.5";
        txtXMax.Text = "3.5";
        txtA.Text = "1.25";
        txtB.Text = "1.5";
        txtC.Text = "0.75";

        // Labels
        CreateLabel("X Min:", new Point(130, 20));
        CreateLabel("X Max:", new Point(130, 50));
        CreateLabel("a:", new Point(130, 80));
        CreateLabel("b:", new Point(130, 110));
        CreateLabel("c:", new Point(130, 140));

        // ComboBox for step
        cmbStep = new ComboBox { Location = new Point(20, 170), Size = new Size(100, 20), DropDownStyle = ComboBoxStyle.DropDownList };
        cmbStep.Items.AddRange(new object[] { 0.1, 0.5, 1.0 });
        cmbStep.SelectedIndex = 1; // Default to 0.5
        this.Controls.Add(cmbStep);
        CreateLabel("Step:", new Point(130, 170));

        // CheckBox for function selection
        chkFunction = new CheckBox { Text = "y = 10 * b * c / x + cos(a * x)", Location = new Point(20, 200), Size = new Size(200, 20), Checked = true };
        this.Controls.Add(chkFunction);

        // RadioButtons for output selection
        rbListBox = new RadioButton { Text = "ListBox", Location = new Point(20, 230), Size = new Size(100, 20), Checked = true };
        rbChart = new RadioButton { Text = "Chart", Location = new Point(130, 230), Size = new Size(100, 20) };
        this.Controls.Add(rbListBox);
        this.Controls.Add(rbChart);

        // Output panel
        panelOutput = new Panel { Location = new Point(250, 20), Size = new Size(500, 500), Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right | AnchorStyles.Bottom };
        this.Controls.Add(panelOutput);

        // Event handlers
        txtXMin.TextChanged += InputChanged;
        txtXMax.TextChanged += InputChanged;
        txtA.TextChanged += InputChanged;
        txtB.TextChanged += InputChanged;
        txtC.TextChanged += InputChanged;
        cmbStep.SelectedIndexChanged += InputChanged;
        chkFunction.CheckedChanged += InputChanged;
        rbListBox.CheckedChanged += OutputChanged;
        rbChart.CheckedChanged += OutputChanged;
        this.Resize += Form_Resize;

        UpdateOutput();
    }

    private TextBox CreateTextBox(string name, Point location, Size size)
    {
        TextBox tb = new TextBox { Name = name, Location = location, Size = size };
        this.Controls.Add(tb);
        return tb;
    }

    private Label CreateLabel(string text, Point location)
    {
        Label lbl = new Label { Text = text, Location = location, Size = new Size(100, 20) };
        this.Controls.Add(lbl);
        return lbl;
    }

    private void InputChanged(object sender, EventArgs e)
    {
        try
        {
            CalculatePoints();
            UpdateOutput();
        }
        catch (Exception ex)
        {
            MessageBox.Show($"Error: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }

    private void OutputChanged(object sender, EventArgs e)
    {
        UpdateOutput();
    }

    private void Form_Resize(object sender, EventArgs e)
    {
        UpdateOutput();
    }

    private void CalculatePoints()
    {
        points.Clear();
        if (!chkFunction.Checked) return;

        if (!double.TryParse(txtXMin.Text, out double xMin) ||
            !double.TryParse(txtXMax.Text, out double xMax) ||
            !double.TryParse(txtA.Text, out double a) ||
            !double.TryParse(txtB.Text, out double b) ||
            !double.TryParse(txtC.Text, out double c) ||
            !double.TryParse(cmbStep.SelectedItem?.ToString(), out double step))
        {
            throw new Exception("Invalid input values.");
        }

        if (xMin >= xMax || step <= 0)
        {
            throw new Exception("Invalid range or step.");
        }

        for (double x = xMin; x <= xMax; x += step)
        {
            if (Math.Abs(x) < 1e-10) continue; // Avoid division by zero
            double y = 10 * b * c / x + Math.Cos(a * x);
            points.Add(new DataPoint(x, y));
        }
    }

    private void UpdateOutput()
    {
        panelOutput.Controls.Clear();
        if (lbPoints != null) lbPoints.Dispose();
        if (chart != null) chart.Dispose();

        if (rbListBox.Checked)
        {
            lbPoints = new ListBox { Dock = DockStyle.Fill };
            panelOutput.Controls.Add(lbPoints);
            foreach (DataPoint point in points)
            {
                lbPoints.Items.Add($"x = {point.X:F2}, y = {point.Y:F2}");
            }
        }
        else if (rbChart.Checked)
        {
            chart = new Chart { Dock = DockStyle.Fill };
            ChartArea area = new ChartArea { Name = "myGraph" };
            if (points.Count > 0)
            {
                area.AxisX.Minimum = points.Min(p => p.X);
                area.AxisX.Maximum = points.Max(p => p.X);
                area.AxisX.MajorGrid.Interval = double.TryParse(cmbStep.SelectedItem?.ToString(), out double step) ? step : 0.5;
            }
            chart.ChartAreas.Add(area);

            Series series = new Series
            {
                ChartArea = "myGraph",
                ChartType = SeriesChartType.Spline,
                BorderWidth = 3,
                LegendText = "y = 10 * b * c / x + cos(a * x)"
            };
            chart.Series.Add(series);
            chart.Legends.Add(new Legend());

            series.Points.DataBindXY(points, "X", points, "Y");
            panelOutput.Controls.Add(chart);
        }
    }
}

public class DataPoint
{
    public double X { get; set; }
    public double Y { get; set; }

    public DataPoint(double x, double y)
    {
        X = x;
        Y = y;
    }
}

public class DataPointCollection
{
    private List<DataPoint> points = new List<DataPoint>();

    public void Add(DataPoint point) => points.Add(point);
    public void Clear() => points.Clear();
    public int Count => points.Count;
    public double Min(Func<DataPoint, double> selector) => points.Min(selector);
    public double Max(Func<DataPoint, double> selector) => points.Max(selector);
    public IEnumerable<DataPoint> Points => points;
}
