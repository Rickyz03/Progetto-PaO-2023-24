#include "AboveChartLabelsCreatorVisitor.h"
#include "GetEmbeddedesensorNumberVisitor.h"

namespace View {

AboveChartLabelsCreatorVisitor::AboveChartLabelsCreatorVisitor(AboveChartWidget* aboveChartWidget) : aboveChartWidget(aboveChartWidget) {}

void AboveChartLabelsCreatorVisitor::visit(const Sensor::DistanceCoveredSensor& distanceCoveredSensor){
    GetEmbeddedesensorNumberVisitor getEmbeddedesensorNumberVisitor(aboveChartWidget);
    distanceCoveredSensor.accept(getEmbeddedesensorNumberVisitor);

    aboveChartWidget->createTheRestOfLabels(distanceCoveredSensor.getMinValue(), distanceCoveredSensor.getMaxValue(), 
                                            distanceCoveredSensor.getMean(), distanceCoveredSensor.getVariance(), distanceCoveredSensor.getLambda());
}

void AboveChartLabelsCreatorVisitor::visit(const Sensor::Chronometer& chronometer){
    GetEmbeddedesensorNumberVisitor getEmbeddedesensorNumberVisitor(aboveChartWidget);
    chronometer.accept(getEmbeddedesensorNumberVisitor);

    aboveChartWidget->createTheRestOfLabels(chronometer.getMinValue(), chronometer.getMaxValue(), chronometer.getMean(), 
                                            chronometer.getVariance(), chronometer.getLambda());
}

void AboveChartLabelsCreatorVisitor::visit(const Sensor::SpeedSensor& speedSensor){
    GetEmbeddedesensorNumberVisitor getEmbeddedesensorNumberVisitor(aboveChartWidget);
    speedSensor.accept(getEmbeddedesensorNumberVisitor);

    const Sensor::DistanceCoveredSensor& distanceCoveredSensor = speedSensor.getDistanceCoveredSensor();    

    aboveChartWidget->createTheRestOfLabels(distanceCoveredSensor.getMinValue(), distanceCoveredSensor.getMaxValue(), 
                                            distanceCoveredSensor.getMean(), distanceCoveredSensor.getVariance(), distanceCoveredSensor.getLambda());
}

void AboveChartLabelsCreatorVisitor::visit(const Sensor::Accelerometer& accelerometer){
    GetEmbeddedesensorNumberVisitor getEmbeddedesensorNumberVisitor(aboveChartWidget);
    accelerometer.accept(getEmbeddedesensorNumberVisitor);

    const Sensor::SpeedSensor& speedSensor = accelerometer.getSpeedSensor();
    const Sensor::DistanceCoveredSensor& distanceCoveredSensor = speedSensor.getDistanceCoveredSensor();

    aboveChartWidget->createTheRestOfLabels(distanceCoveredSensor.getMinValue(), distanceCoveredSensor.getMaxValue(), 
                                            distanceCoveredSensor.getMean(), distanceCoveredSensor.getVariance(), distanceCoveredSensor.getLambda());
}

}