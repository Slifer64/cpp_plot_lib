#include <exception>
#include <cstring>
#include <iostream>

#include <armadillo>
#include <plot_lib/qt_plot.h>

using namespace as64_;

int main(int argc, char **argv)
{
  // ros::init(argc, argv, "plot_lib_example");

  // ============== Create some data ===============
  int n_data = 2000;
	arma::rowvec Time = arma::linspace<arma::rowvec>(0, 5, n_data);
	arma::mat P_data(3, n_data);
  
  P_data.row(0) = arma::sin(Time);
  P_data.row(1) = arma::cos(Time);
  P_data.row(2) = arma::pow(arma::sin(Time), 2);

  arma::mat dP_data(P_data.n_rows, P_data.n_cols);
  arma::rowvec dTime = arma::diff(Time);
  for (int i=0; i<P_data.n_rows; i++)
    dP_data.row(i) = arma::join_horiz(arma::diff(P_data.row(i))/dTime, arma::vec({0}));

  // =============== Plot data ==============
  std::cerr << "Plotting logged data...\n";

  pl_::QtPlot::init(); // Run this once, before executing any other plot command

  // create a figure and axes object for convenience
  pl_::Figure *fig;
  pl_::Axes *ax;

  fig = pl_::figure("", {500, 600});
  fig->setAxes(2,1); // create a figure with 2 x 1 axes


  ax = fig->getAxes(0);
  ax->hold(true);
  // ax->xlabel("time [s]");
  for (int i=0;i<P_data.n_rows;i++) pl_::Graph *graph = ax->plot(Time, P_data.row(i), pl_::LineWidth_,2.0);
  ax->title("Cartesian Position", pl_::FontSize_,16, pl_::FontWeight_,pl_::DemiBold);
  ax->ylabel("Position [m]", pl_::FontSize_,14);
  ax->legend({"x", "y", "z"}, pl_::FontSize_,15);
  ax->drawnow();

  ax = fig->getAxes(1);
  ax->hold(true);
  // ax->xlabel("time [s]");
  for (int i=0;i<dP_data.n_rows;i++) ax->plot(Time, dP_data.row(i), pl_::LineWidth_,2.0);
  // ax->title("Cartesian Velocity");
  ax->ylabel("Velocity [m/s]", pl_::FontSize_,14);
  ax->xlabel("Time [s]", pl_::FontSize_,14);
  ax->legend({"x", "y", "z"}, pl_::FontSize_,15);
  ax->drawnow();

	std::cerr << "Press [enter] to exit...\n";
  std::string dummy;
	std::getline(std::cin, dummy, '\n');

	std::cerr << "Finished!!!\n";


  return 0;
}


