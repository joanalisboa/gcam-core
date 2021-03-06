% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/zchunk_LB132.ag_an_For_Prices_USA_C_2005.R
\name{module_aglu_LB132.ag_an_For_Prices_USA_C_2005}
\alias{module_aglu_LB132.ag_an_For_Prices_USA_C_2005}
\title{module_aglu_LB132.ag_an_For_Prices_USA_C_2005}
\usage{
module_aglu_LB132.ag_an_For_Prices_USA_C_2005(command, ...)
}
\arguments{
\item{command}{API command to execute}

\item{...}{other optional parameters, depending on command}
}
\value{
Depends on \code{command}: either a vector of required inputs,
a vector of output names, or (if \code{command} is "MAKE") all
the generated outputs: \code{L132.ag_an_For_Prices}. The corresponding file in the
original data system was \code{LB132.ag_an_For_Prices_USA_C_2005.R} (aglu level1).
}
\description{
Calculate the calibration prices for all GCAM AGLU commodities.
}
\details{
This chunk calculates average prices over calibration years by GCAM commodity.
Averages across years are unweighted; averages over FAO item are weighted by production.
}
\author{
RC April 2017
}
