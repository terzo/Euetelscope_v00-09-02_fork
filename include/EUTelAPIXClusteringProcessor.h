// Version: $Id: EUTelAPIXClusteringProcessor.h 2296 2013-01-19 09:09:21Z hamnett $

#ifndef EUTELAPIXCLUSTERINGPROCESSOR_H
#define EUTELAPIXCLUSTERINGPROCESSOR_H 1

// since v00-00-09 built only if GEAR is available
#ifdef USE_GEAR

// eutelescope includes ".h"
#include "EUTelExceptions.h"
#include "EUTELESCOPE.h"
#include "EUTelRunHeaderImpl.h"
#include "EUTelEventImpl.h"
#include "EUTelAPIXClusteringProcessor.h"
#include "EUTelVirtualCluster.h"
#include "EUTelFFClusterImpl.h"
#include "EUTelDFFClusterImpl.h"
#include "EUTelBrickedClusterImpl.h"
#include "EUTelExceptions.h"
#include "EUTelHistogramManager.h"
#include "EUTelMatrixDecoder.h"
#include "EUTelSparseDataImpl.h"
#include "EUTelSparseClusterImpl.h"
#include "EUTelSparseData2Impl.h"
#include "EUTelSparseCluster2Impl.h"

// marlin includes ".h"
#include "marlin/EventModifier.h"
#include "marlin/Processor.h"
#include "marlin/Exceptions.h"

// gear includes <.h>
#include <gear/SiPlanesParameters.h>
#include <gear/SiPlanesLayerLayout.h>

// aida includes <.h>
#if defined(USE_AIDA) || defined(MARLIN_USE_AIDA)
#include <AIDA/IBaseHistogram.h>
#endif

// lcio includes <.h>
#include <IMPL/TrackerRawDataImpl.h>
#include <IMPL/LCCollectionVec.h>

// system includes <>
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <list>

namespace eutelescope {


  class EUTelAPIXClusteringProcessor : public marlin::Processor , public marlin::EventModifier {

  public:
    
    virtual Processor * newProcessor() {
      return new EUTelAPIXClusteringProcessor;
    }
    
    EUTelAPIXClusteringProcessor();

    virtual const std::string & name() const { return Processor::name() ; }
    virtual void init ();
    virtual void processRunHeader (LCRunHeader * run);
    virtual void processEvent (LCEvent * evt);
    virtual void modifyEvent( LCEvent * evt ) ;
    virtual void check (LCEvent * evt);
    virtual void end();

#if defined(USE_AIDA) || defined(MARLIN_USE_AIDA)
	void bookHistos();
	void fillHistos(LCEvent * evt);
	static std::string _clusterSignalHistoName;
	static std::string _seedSignalHistoName;
	static std::string _hitMapHistoName;
	static std::string _pixelMapHistoName;
	static std::string _seedSNRHistoName;
	static std::string _clusterNoiseHistoName;
	static std::string _clusterSNRHistoName;
	static std::string _eventMultiplicityHistoName;
	static std::string _pixelSignalHistoName;
	static std::string _clusterSizeName;
	static std::string _clusterSizeXName;
	static std::string _clusterSizeYName;
	static std::string _clusterHolesXName;
	static std::string _clusterHolesYName;
	static std::string _lvl1TriggerName;
	static std::string _lvl1TriggerDiffName;
#endif
    void initializeGeometry( LCEvent * event ) throw ( marlin::SkipEventException );
    
    protected:
	void Clustering(LCEvent * evt, LCCollectionVec * pulse);
	std::string _zsDataCollectionName;
	std::string _clusterCollectionName;
        int _iRun;
	int _iEvt; 
	bool _isFirstEvent;
	unsigned int _initialClusterCollectionSize;
	int _minNPixels;
	int _minXDistance;
	int _minYDistance;
	int _minDiagDistance;
	int _minCharge;
	int _minLVL1;
	int _maxXsize;
	int _maxYsize;
	int _minXsize;
	int _minYsize;
        std::vector<int> _ClusterLimits;
        std::map<int, std::vector<int> > _ClusterLimitsMap;


	bool _fillHistos;
    
	int _noOfDetector;
	bool _isGeometryReady;
	std::vector<int> _sensorIDVec;
	gear::SiPlanesParameters* _siPlanesParameters;
	gear::SiPlanesLayerLayout*_siPlanesLayerLayout;
	std::map< int , int > _layerIndexMap;
	std::vector< int > _orderedSensorIDVec;
	   
	
	std::string _histoInfoFileName;
	std::vector<int > _clusterSpectraNVector;
	std::vector<int > _clusterSpectraNxNVector;
	std::map<std::string , AIDA::IBaseHistogram * > _aidaHistoMap;
	
	bool addCluster (eutelescope::EUTelSparseClusterImpl< eutelescope::EUTelAPIXSparsePixel >  *apixCluster, int& sensorID);

        //! Total cluster found
        /*! This is a map correlating the sensorID number and the
        *  total number of clusters found on that sensor.
        *  The content of this map is show during end().
        */
        std::map< int, int > _totClusterMap;


  };

  //! A global instance of the processor
  EUTelAPIXClusteringProcessor gEUTelAPIXClusteringProcessor;

}
#endif // USE_GEAR
#endif
