/**
 * This code is part of Qiskit.
 *
 * (C) Copyright IBM 2018, 2019, 2020.
 *
 * This code is licensed under the Apache License, Version 2.0. You may
 * obtain a copy of this license in the LICENSE.txt file in the root directory
 * of this source tree or at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * Any modifications or derivative works of this code must retain this
 * copyright notice, and modified files need to carry a notice indicating
 * that they have been altered from the originals.
 */

#ifndef _aer_framework_result_pybind_data_hpp_
#define _aer_framework_result_pybind_data_hpp_

#include "framework/pybind_basics.hpp"
#include "framework/results/experiment_data.hpp"

//------------------------------------------------------------------------------
// Aer C++ -> Python Conversion
//------------------------------------------------------------------------------

namespace AerToPy {

/**
 * Convert a AverageData to a python object
 * @param avg_data is an AverageData
 * @returns a py::dict
 */
template<typename T>
py::object from_avg_data(AER::AverageData<T> &&avg_data);
template<typename T>
py::object from_avg_data(AER::AverageData<T> &avg_data);

// JSON specialization
template<>
py::object from_avg_data(AER::AverageData<json_t> &&avg_data);

/**
 * Convert a AverageData to a python object
 * @param avg_data is an AverageData
 * @returns a py::dict
 */
template<typename T>
py::object from_avg_data(AER::AverageData<matrix<T>> &&avg_data);
template<typename T>
py::object from_avg_data(AER::AverageData<matrix<T>> &avg_data);


/**
 * Convert a AverageData to a python object
 * @param avg_data is an AverageData
 * @returns a py::dict
 */
template<typename T>
py::object from_avg_data(AER::AverageData<AER::Vector<T>> &&avg_data);
template<typename T>
py::object from_avg_data(AER::AverageData<AER::Vector<T>> &avg_data);

/**
 * Convert a AverageData to a python object
 * @param avg_data is an AverageData
 * @returns a py::dict
 */
template<typename T>
py::object from_avg_data(AER::AverageData<std::vector<T>> &&avg_data);
template<typename T>
py::object from_avg_data(AER::AverageData<std::vector<T>> &avg_data);

/**
 * Convert a AverageSnapshot to a python object
 * @param avg_snap is an AverageSnapshot
 * @returns a py::dict
 */
template<typename T>
py::object from_avg_snap(AER::AverageSnapshot<T> &&avg_snap);
template<typename T>
py::object from_avg_snap(AER::AverageSnapshot<T> &avg_snap);

/**
 * Convert a PershotSnapshot  to a python object
 * @param avg_snap is an PershotSnapshot 
 * @returns a py::dict
 */
template<typename T>
py::object from_pershot_snap(AER::PershotSnapshot<T> &&snap);
template<typename T>
py::object from_pershot_snap(AER::PershotSnapshot<T> &snap);

/**
 * Convert a PershotData to a python object
 * @param data is an PershotData
 * @returns a py::dict
 */
template<typename T>
py::object from_pershot_data(AER::PershotData<T> &&data);
template<typename T>
py::object from_pershot_data(AER::PershotData<T> &data);

// JSON specialization
template<>
py::object from_pershot_data(AER::PershotData<json_t> &&avg_data);

/**
 * Convert a PershotData to a python object
 * @param data is an PershotData
 * @returns a py::dict
 */
template<typename T>
py::object from_pershot_data(AER::PershotData<matrix<T>> &&data);
template<typename T>
py::object from_pershot_data(AER::PershotData<matrix<T>> &data);


/**
 * Convert a PershotData to a python object
 * @param data is an PershotData
 * @returns a py::dict
 */
template<typename T>
py::object from_pershot_data(AER::PershotData<AER::Vector<T>> &&data);
template<typename T>
py::object from_pershot_data(AER::PershotData<AER::Vector<T>> &data);

/**
 * Convert a PershotData to a python object
 * @param data is an PershotData
 * @returns a py::dict
 */
template<typename T>
py::object from_pershot_data(AER::PershotData<std::vector<T>> &&data);
template<typename T>
py::object from_pershot_data(AER::PershotData<std::vector<T>> &data);

/**
 * Convert an ExperimentData to a python object
 * @param result is an ExperimentData
 * @returns a py::dict
 */
py::object from_data(AER::ExperimentData &&result);
py::object from_data(AER::ExperimentData &result);

} //end namespace AerToPy


/*******************************************************************************
 *
 * Implementations
 *
 ******************************************************************************/

//============================================================================
// Pybind Conversion for Simulator types
//============================================================================

template<typename T> 
py::object AerToPy::from_avg_data(AER::AverageData<T> &avg_data) {
  return AerToPy::from_avg_data(std::move(avg_data));
}

template<typename T> 
py::object AerToPy::from_avg_data(AER::AverageData<T> &&avg_data) {
  py::dict d;
  d["value"] = std::move(avg_data.mean());
  if (avg_data.has_variance()) {
    d["variance"] = std::move(avg_data.variance());
  }
  return std::move(d);
}

template <> 
py::object AerToPy::from_avg_data(AER::AverageData<json_t> &&avg_data) {
  py::dict d;
  py::object py_mean;
  from_json(avg_data.mean(), py_mean);
  d["value"] = std::move(py_mean);
  if (avg_data.has_variance()) {
    py::object py_var;
    from_json(avg_data.variance(), py_var);
    d["variance"] = std::move(py_var);
  }
  return std::move(d);
}

template<typename T> 
py::object AerToPy::from_avg_data(AER::AverageData<AER::Vector<T>> &avg_data) {
  return AerToPy::from_avg_data(std::move(avg_data));
}

template<typename T> 
py::object AerToPy::from_avg_data(AER::AverageData<AER::Vector<T>> &&avg_data) {
  py::dict d;
  d["value"] = AerToPy::to_numpy(std::move(avg_data.mean()));
  if (avg_data.has_variance()) {
    d["variance"] = AerToPy::to_numpy(std::move(avg_data.variance()));
  }
  return std::move(d);
}

template<typename T> 
py::object AerToPy::from_avg_data(AER::AverageData<matrix<T>> &avg_data) {
  return AerToPy::from_avg_data(std::move(avg_data));
}

template<typename T> 
py::object AerToPy::from_avg_data(AER::AverageData<matrix<T>> &&avg_data) {
  py::dict d;
  d["value"] = AerToPy::to_numpy(std::move(avg_data.mean()));
  if (avg_data.has_variance()) {
    d["variance"] = AerToPy::to_numpy(std::move(avg_data.variance()));
  }
  return std::move(d);
}

template<typename T> 
py::object AerToPy::from_avg_data(AER::AverageData<std::vector<T>> &avg_data) {
  return AerToPy::from_avg_data(std::move(avg_data));
}

template<typename T> 
py::object AerToPy::from_avg_data(AER::AverageData<std::vector<T>> &&avg_data) {
  py::dict d;
  d["value"] = AerToPy::to_numpy(std::move(avg_data.mean()));
  if (avg_data.has_variance()) {
    d["variance"] = AerToPy::to_numpy(std::move(avg_data.variance()));
  }
  return std::move(d);
}

template<typename T> 
py::object AerToPy::from_avg_snap(AER::AverageSnapshot<T> &avg_snap) {
  return AerToPy::from_avg_snap(std::move(avg_snap));
}

template<typename T> 
py::object AerToPy::from_avg_snap(AER::AverageSnapshot<T> &&avg_snap) {
  py::dict d;
  for (auto &outer_pair : avg_snap.data()) {
    py::list d1;
    for (auto &inner_pair : outer_pair.second) {
      // Store mean and variance for snapshot
      py::dict datum = AerToPy::from_avg_data(inner_pair.second);
      // Add memory key if there are classical registers
      auto memory = inner_pair.first;
      if ( ! memory.empty()) {
        datum["memory"] = inner_pair.first;
      }
      // Add to list of output
      d1.append(std::move(datum));
    }
    d[outer_pair.first.data()] = std::move(d1);
  }
  return std::move(d);
}

template<typename T> 
py::object AerToPy::from_pershot_snap(AER::PershotSnapshot<T> &snap) {
  return AerToPy::from_pershot_snap(std::move(snap));
}
template<typename T> 
py::object AerToPy::from_pershot_snap(AER::PershotSnapshot<T> &&snap) {
  py::dict d;
  // string PershotData
  for (auto &pair : snap.data())
    d[pair.first.data()] = AerToPy::from_pershot_data(pair.second);
  return std::move(d);
}

template<typename T>
py::object AerToPy::from_pershot_data(AER::PershotData<T> &&data) {
  return py::cast(data.data(), py::return_value_policy::move);
}

template<typename T>
py::object AerToPy::from_pershot_data(AER::PershotData<T> &data) {
  return AerToPy::from_pershot_data(std::move(data));
}

template<>
py::object AerToPy::from_pershot_data(AER::PershotData<json_t> &&data) {
  py::object tmp;
  from_json(data.data(), tmp);
  return tmp;
}

template<typename T>
py::object AerToPy::from_pershot_data(AER::PershotData<matrix<T>> &&data) {
  py::list l;
  for (auto &item : data.data()) {
    l.append(AerToPy::to_numpy(std::move(item)));
  }
  return std::move(l);
}

template<typename T>
py::object AerToPy::from_pershot_data(AER::PershotData<matrix<T>> &data) {
  return AerToPy::from_pershot_data(std::move(data));
}



template<typename T>
py::object AerToPy::from_pershot_data(AER::PershotData<AER::Vector<T>> &&data) {
  py::list l;
  for (auto &item : data.data()) {
    l.append(AerToPy::to_numpy(std::move(item)));
  }
  return std::move(l);
}

template<typename T>
py::object AerToPy::from_pershot_data(AER::PershotData<AER::Vector<T>> &data) {
  return AerToPy::from_pershot_data(std::move(data));
}



template<typename T>
py::object AerToPy::from_pershot_data(AER::PershotData<std::vector<T>> &&data) {
  py::list l;
  for (auto &item : data.data()) {
    l.append(AerToPy::to_numpy(std::move(item)));
  }
  return std::move(l);
}

template<typename T>
py::object AerToPy::from_pershot_data(AER::PershotData<std::vector<T>> &data) {
  return AerToPy::from_pershot_data(std::move(data));
}


py::object AerToPy::from_data(AER::ExperimentData &datum) {
  return AerToPy::from_data(std::move(datum));
}

py::object AerToPy::from_data(AER::ExperimentData &&datum) {
  py::dict pydata;

  // Measure data
  if (datum.return_counts_ && ! datum.counts_.empty()) {
    pydata["counts"] = std::move(datum.counts_);
  }
  if (datum.return_memory_ && ! datum.memory_.empty()) {
    pydata["memory"] = std::move(datum.memory_);
  }
  if (datum.return_register_ && ! datum.register_.empty()) {
    pydata["register"] = std::move(datum.register_);
  }

  // Add additional data
  for (auto &pair : datum.additional_data<json_t>()) {
    py::object tmp;
    from_json(pair.second, tmp);
    pydata[pair.first.data()] = std::move(tmp);
  }
  for (auto &pair : datum.additional_data<std::complex<double>>()) {
    pydata[pair.first.data()] = pair.second;
  }
  for (auto &pair : datum.additional_data<std::vector<std::complex<float>>>()) {
    pydata[pair.first.data()] = AerToPy::to_numpy(std::move(pair.second));
  }
  for (auto &pair : datum.additional_data<std::vector<std::complex<double>>>()) {
    pydata[pair.first.data()] = AerToPy::to_numpy(std::move(pair.second));
  }
  for (auto &pair : datum.additional_data<AER::Vector<std::complex<float>>>()) {
    pydata[pair.first.data()] = AerToPy::to_numpy(std::move(pair.second));
  }
  for (auto &pair : datum.additional_data<AER::Vector<std::complex<double>>>()) {
    pydata[pair.first.data()] = AerToPy::to_numpy(std::move(pair.second));
  }
  for (auto &pair : datum.additional_data<matrix<std::complex<float>>>()) {
    pydata[pair.first.data()] = AerToPy::to_numpy(std::move(pair.second));    
  }
  for (auto &pair : datum.additional_data<matrix<std::complex<double>>>()) {
    pydata[pair.first.data()] = AerToPy::to_numpy(std::move(pair.second));    
  }
  for (auto &pair : datum.additional_data<std::map<std::string, std::complex<double>>>()) {
    pydata[pair.first.data()] = pair.second;
  }
  for (auto &pair : datum.additional_data<std::map<std::string, double>>()) {
    pydata[pair.first.data()] = pair.second;
  }

  // Snapshot data
  if (datum.return_snapshots_) {
    py::dict snapshots;
  
    // Average snapshots
    for (auto &pair : datum.average_snapshots<json_t>()) {
      snapshots[pair.first.data()] = AerToPy::from_avg_snap(pair.second);
    }
    for (auto &pair : datum.average_snapshots<std::complex<double>>()) {
      snapshots[pair.first.data()] = AerToPy::from_avg_snap(pair.second);
    }
    for (auto &pair : datum.average_snapshots<std::vector<std::complex<float>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_avg_snap(pair.second);
    }
    for (auto &pair : datum.average_snapshots<std::vector<std::complex<double>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_avg_snap(pair.second);
    }
    for (auto &pair : datum.average_snapshots<AER::Vector<std::complex<float>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_avg_snap(pair.second);
    }
    for (auto &pair : datum.average_snapshots<AER::Vector<std::complex<double>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_avg_snap(pair.second);
    }
    for (auto &pair : datum.average_snapshots<matrix<std::complex<float>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_avg_snap(pair.second);
    }
    for (auto &pair : datum.average_snapshots<matrix<std::complex<double>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_avg_snap(pair.second);
    }
    for (auto &pair : datum.average_snapshots<std::map<std::string, std::complex<double>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_avg_snap(pair.second);
    }
    for (auto &pair : datum.average_snapshots<std::map<std::string, double>>()) {
      snapshots[pair.first.data()] = AerToPy::from_avg_snap(pair.second);
    }
    // Singleshot snapshot data
    // Note these will override the average snapshots
    // if they share the same type string
    
    for (auto &pair : datum.pershot_snapshots<json_t>()) {
      snapshots[pair.first.data()] = AerToPy::from_pershot_snap(pair.second);
    }
    for (auto &pair : datum.pershot_snapshots<std::complex<double>>()) {
      snapshots[pair.first.data()] = AerToPy::from_pershot_snap(pair.second);
    }
    for (auto &pair : datum.pershot_snapshots<std::vector<std::complex<float>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_pershot_snap(pair.second);
    }
    for (auto &pair : datum.pershot_snapshots<std::vector<std::complex<double>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_pershot_snap(pair.second);
    }
    for (auto &pair : datum.pershot_snapshots<AER::Vector<std::complex<float>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_pershot_snap(pair.second);
    }
    for (auto &pair : datum.pershot_snapshots<AER::Vector<std::complex<double>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_pershot_snap(pair.second);
    }
    for (auto &pair : datum.pershot_snapshots<matrix<std::complex<float>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_pershot_snap(pair.second);
    }
    for (auto &pair : datum.pershot_snapshots<matrix<std::complex<double>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_pershot_snap(pair.second);
    }
    for (auto &pair : datum.pershot_snapshots<std::map<std::string, std::complex<double>>>()) {
      snapshots[pair.first.data()] = AerToPy::from_pershot_snap(pair.second);
    }
    for (auto &pair : datum.pershot_snapshots<std::map<std::string, double>>()) {
      snapshots[pair.first.data()] = AerToPy::from_pershot_snap(pair.second);
    }

    if ( py::len(snapshots) != 0 )
        pydata["snapshots"] = std::move(snapshots);
  }
  //for (auto item : pydatum)
  //  py::print("    {}:, {}"_s.format(item.first, item.second));
  return std::move(pydata);
}

#endif
