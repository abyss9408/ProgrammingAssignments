#include "plot_hull.h"
#include "nlohmann_json.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

using json = nlohmann::json;

void plot_hull(const std::vector<Point> &points, const std::vector<Point> &hull,
               const std::string &filename) {
  json points_json = json::array();
  for (size_t i = 0; i < points.size(); ++i) {
    const auto &p = points[i];
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(2);
    oss << "Index " << i << ":<br>(" << p.x << ", " << p.y << ")";
    points_json.push_back({{"x", p.x}, {"y", p.y}, {"info", oss.str()}});
  }

  json hull_json = json::array();
  for (const auto &p : hull) {
    hull_json.push_back({{"x", p.x}, {"y", p.y}});
  }

  auto [min_x, max_x] = std::minmax_element(
      points.begin(), points.end(),
      [](const Point &a, const Point &b) { return a.x < b.x; });
  auto [min_y, max_y] = std::minmax_element(
      points.begin(), points.end(),
      [](const Point &a, const Point &b) { return a.y < b.y; });

  double x_range = max_x->x - min_x->x;
  double y_range = max_y->y - min_y->y;
  double x_padding = 0.05 * x_range;
  double y_padding = 0.05 * y_range;

  double x_min = min_x->x - x_padding;
  double x_max = max_x->x + x_padding;
  double y_min = min_y->y - y_padding;
  double y_max = max_y->y + y_padding;

  double max_range = std::max(x_range + 2 * x_padding, y_range + 2 * y_padding);
  double x_center = (x_min + x_max) / 2;
  double y_center = (y_min + y_max) / 2;

  x_min = x_center - max_range / 2;
  x_max = x_center + max_range / 2;
  y_min = y_center - max_range / 2;
  y_max = y_center + max_range / 2;

  std::ofstream file(filename);
  file << R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Convex Hull</title>
    <script src="https://d3js.org/d3.v6.min.js"></script>
    <style>
        .tooltip {
            position: absolute;
            text-align: center;
            width: auto;
            height: auto;
            padding: 5px;
            font: 12px sans-serif;
            background: lightsteelblue;
            border: 0px;
            border-radius: 8px;
            pointer-events: none;
        }
        .legend {
            font: 12px sans-serif;
        }
    </style>
</head>
<body>
    <svg width="600" height="600"></svg>
    <script type="text/javascript">
        const points = )"
       << points_json.dump() << R"(;
        const hull = )"
       << hull_json.dump() << R"(;

        const width = 600;
        const height = 600;
        const margin = 60;

        const xScale = d3.scaleLinear()
            .domain([)"
       << x_min << ", " << x_max << R"(])
            .range([margin, width - margin - 60]);

        const yScale = d3.scaleLinear()
            .domain([)"
       << y_min << ", " << y_max << R"(])
            .range([height - margin, margin]);

        const svg = d3.select("svg");

        svg.append("g")
            .attr("class", "grid")
            .attr("transform", `translate(0,${height - margin})`)
            .call(d3.axisBottom(xScale)
                .ticks(10)
                .tickSize(-height + 2 * margin)
                .tickFormat(""))
            .selectAll("line")
            .attr("stroke", "lightgray")
            .attr("stroke-width", 0.5);

        svg.append("g")
            .attr("class", "grid")
            .attr("transform", `translate(${margin},0)`)
            .call(d3.axisLeft(yScale)
                .ticks(10)
                .tickSize(-width + 2 * margin + 60)
                .tickFormat(""))
            .selectAll("line")
            .attr("stroke", "lightgray")
            .attr("stroke-width", 0.5);

        svg.append("g")
            .attr("transform", `translate(0,${height - margin})`)
            .call(d3.axisBottom(xScale).ticks(10))
            .append("text")
            .attr("x", (width - margin - 60) / 2)
            .attr("y", 40)
            .attr("fill", "black")
            .style("text-anchor", "middle")
            .text("x");

        svg.append("g")
            .attr("transform", `translate(${margin},0)`)
            .call(d3.axisLeft(yScale).ticks(10))
            .append("text")
            .attr("x", -40)
            .attr("y", height / 2)
            .attr("dy", "-1em")
            .attr("fill", "black")
            .style("text-anchor", "middle")
            .text("y");

        const tooltip = d3.select("body").append("div")
            .attr("class", "tooltip")
            .style("opacity", 0);

        const hullPoints = d3.polygonHull(points.map(d => [xScale(d.x), yScale(d.y)]));
        if (hullPoints) {
            hullPoints.push(hullPoints[0]);
            svg.append("path")
                .attr("d", d3.line()(hullPoints))
                .attr("fill", "none")
                .attr("stroke", "#fb9a99")
                .attr("stroke-width", 6);
        }

        const hullClosed = hull.concat([hull[0]]);
        svg.append("path")
            .datum(hullClosed)
            .attr("fill", "none")
            .attr("stroke", "#1f78b4")
            .attr("stroke-width", 2)
            .attr("d", d3.line()
                .x(d => xScale(d.x))
                .y(d => yScale(d.y))
            );

        svg.selectAll("circle")
            .data(points)
            .enter()
            .append("circle")
            .attr("cx", d => xScale(d.x))
            .attr("cy", d => yScale(d.y))
            .attr("r", 3)
            .attr("fill", "black")
            .on("mouseover", function(event, d) {
                tooltip.transition()
                    .duration(200)
                    .style("opacity", .9);
                tooltip.html(d.info)
                    .style("left", (event.pageX + 5) + "px")
                    .style("top", (event.pageY - 28) + "px");
            })
            .on("mouseout", function(d) {
                tooltip.transition()
                    .duration(500)
                    .style("opacity", 0);
            });

        const legend = svg.append("g")
            .attr("class", "legend")
            .attr("transform", `translate(${width - margin - 40}, ${margin})`);

        legend.append("line")
            .attr("x1", 0)
            .attr("x2", 18)
            .attr("y1", 0)
            .attr("y2", 0)
            .attr("stroke", "#fb9a99")
            .attr("stroke-width", 6);

        legend.append("text")
            .attr("x", 24)
            .attr("y", 0)
            .attr("dy", "0.35em")
            .style("text-anchor", "start")
            .text("Convex Hull");

        legend.append("line")
            .attr("x1", 0)
            .attr("x2", 18)
            .attr("y1", 20)
            .attr("y2", 20)
            .attr("stroke", "#1f78b4")
            .attr("stroke-width", 2);

        legend.append("text")
            .attr("x", 24)
            .attr("y", 20)
            .attr("dy", "0.35em")
            .style("text-anchor", "start")
            .text("Your Solution");

    </script>
</body>
</html>
)";
  file.close();
}