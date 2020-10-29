/* ====================================================================
 * Copyright (c) 2004-2019 Open Source Applications Foundation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * ====================================================================
 */

#include "common.h"
#include "structmember.h"

#include "bases.h"
#include "measureunit.h"
#include "macros.h"

#if U_ICU_VERSION_HEX >= 0x04020000
DECLARE_CONSTANTS_TYPE(UTimeUnitFields)
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(67, 0, 0)
DECLARE_CONSTANTS_TYPE(UMeasureUnitComplexity)
#endif

/* MeasureUnit */

class t_measureunit : public _wrapper {
public:
    MeasureUnit *object;
};

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
static PyObject *t_measureunit_getType(t_measureunit *self);
static PyObject *t_measureunit_getSubtype(t_measureunit *self);
static PyObject *t_measureunit_getAvailable(PyTypeObject *type, PyObject *arg);
static PyObject *t_measureunit_getAvailableTypes(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(67, 0, 0)
static PyObject *t_measureunit_getIdentifier(t_measureunit *self);
static PyObject *t_measureunit_getComplexity(t_measureunit *self);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
static PyObject *t_measureunit_createAcre(PyTypeObject *type);
static PyObject *t_measureunit_createArcMinute(PyTypeObject *type);
static PyObject *t_measureunit_createArcSecond(PyTypeObject *type);
static PyObject *t_measureunit_createCelsius(PyTypeObject *type);
static PyObject *t_measureunit_createCentimeter(PyTypeObject *type);
static PyObject *t_measureunit_createCubicKilometer(PyTypeObject *type);
static PyObject *t_measureunit_createCubicMile(PyTypeObject *type);
static PyObject *t_measureunit_createDay(PyTypeObject *type);
static PyObject *t_measureunit_createDegree(PyTypeObject *type);
static PyObject *t_measureunit_createFahrenheit(PyTypeObject *type);
static PyObject *t_measureunit_createFoot(PyTypeObject *type);
static PyObject *t_measureunit_createGForce(PyTypeObject *type);
static PyObject *t_measureunit_createGram(PyTypeObject *type);
static PyObject *t_measureunit_createHectare(PyTypeObject *type);
static PyObject *t_measureunit_createHectopascal(PyTypeObject *type);
static PyObject *t_measureunit_createHorsepower(PyTypeObject *type);
static PyObject *t_measureunit_createHour(PyTypeObject *type);
static PyObject *t_measureunit_createInch(PyTypeObject *type);
static PyObject *t_measureunit_createInchHg(PyTypeObject *type);
static PyObject *t_measureunit_createKilogram(PyTypeObject *type);
static PyObject *t_measureunit_createKilometer(PyTypeObject *type);
static PyObject *t_measureunit_createKilometerPerHour(PyTypeObject *type);
static PyObject *t_measureunit_createKilowatt(PyTypeObject *type);
static PyObject *t_measureunit_createLightYear(PyTypeObject *type);
static PyObject *t_measureunit_createLiter(PyTypeObject *type);
static PyObject *t_measureunit_createMeter(PyTypeObject *type);
static PyObject *t_measureunit_createMeterPerSecond(PyTypeObject *type);
static PyObject *t_measureunit_createMile(PyTypeObject *type);
static PyObject *t_measureunit_createMilePerHour(PyTypeObject *type);
static PyObject *t_measureunit_createMillibar(PyTypeObject *type);
static PyObject *t_measureunit_createMillimeter(PyTypeObject *type);
static PyObject *t_measureunit_createMillisecond(PyTypeObject *type);
static PyObject *t_measureunit_createMinute(PyTypeObject *type);
static PyObject *t_measureunit_createMonth(PyTypeObject *type);
static PyObject *t_measureunit_createOunce(PyTypeObject *type);
static PyObject *t_measureunit_createPicometer(PyTypeObject *type);
static PyObject *t_measureunit_createPound(PyTypeObject *type);
static PyObject *t_measureunit_createSecond(PyTypeObject *type);
static PyObject *t_measureunit_createSquareFoot(PyTypeObject *type);
static PyObject *t_measureunit_createSquareKilometer(PyTypeObject *type);
static PyObject *t_measureunit_createSquareMeter(PyTypeObject *type);
static PyObject *t_measureunit_createSquareMile(PyTypeObject *type);
static PyObject *t_measureunit_createWatt(PyTypeObject *type);
static PyObject *t_measureunit_createWeek(PyTypeObject *type);
static PyObject *t_measureunit_createYard(PyTypeObject *type);
static PyObject *t_measureunit_createYear(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)
static PyObject *t_measureunit_createAcreFoot(PyTypeObject *type);
static PyObject *t_measureunit_createAmpere(PyTypeObject *type);
static PyObject *t_measureunit_createAstronomicalUnit(PyTypeObject *type);
static PyObject *t_measureunit_createBit(PyTypeObject *type);
static PyObject *t_measureunit_createBushel(PyTypeObject *type);
static PyObject *t_measureunit_createByte(PyTypeObject *type);
static PyObject *t_measureunit_createCalorie(PyTypeObject *type);
static PyObject *t_measureunit_createCarat(PyTypeObject *type);
static PyObject *t_measureunit_createCentiliter(PyTypeObject *type);
static PyObject *t_measureunit_createCubicCentimeter(PyTypeObject *type);
static PyObject *t_measureunit_createCubicFoot(PyTypeObject *type);
static PyObject *t_measureunit_createCubicInch(PyTypeObject *type);
static PyObject *t_measureunit_createCubicMeter(PyTypeObject *type);
static PyObject *t_measureunit_createCubicYard(PyTypeObject *type);
static PyObject *t_measureunit_createCup(PyTypeObject *type);
static PyObject *t_measureunit_createDeciliter(PyTypeObject *type);
static PyObject *t_measureunit_createDecimeter(PyTypeObject *type);
static PyObject *t_measureunit_createFathom(PyTypeObject *type);
static PyObject *t_measureunit_createFluidOunce(PyTypeObject *type);
static PyObject *t_measureunit_createFoodcalorie(PyTypeObject *type);
static PyObject *t_measureunit_createFurlong(PyTypeObject *type);
static PyObject *t_measureunit_createGallon(PyTypeObject *type);
static PyObject *t_measureunit_createGigabit(PyTypeObject *type);
static PyObject *t_measureunit_createGigabyte(PyTypeObject *type);
static PyObject *t_measureunit_createGigahertz(PyTypeObject *type);
static PyObject *t_measureunit_createGigawatt(PyTypeObject *type);
static PyObject *t_measureunit_createHectoliter(PyTypeObject *type);
static PyObject *t_measureunit_createHertz(PyTypeObject *type);
static PyObject *t_measureunit_createJoule(PyTypeObject *type);
static PyObject *t_measureunit_createKarat(PyTypeObject *type);
static PyObject *t_measureunit_createKelvin(PyTypeObject *type);
static PyObject *t_measureunit_createKilobit(PyTypeObject *type);
static PyObject *t_measureunit_createKilobyte(PyTypeObject *type);
static PyObject *t_measureunit_createKilocalorie(PyTypeObject *type);
static PyObject *t_measureunit_createKilohertz(PyTypeObject *type);
static PyObject *t_measureunit_createKilojoule(PyTypeObject *type);
static PyObject *t_measureunit_createKilowattHour(PyTypeObject *type);
static PyObject *t_measureunit_createLiterPerKilometer(PyTypeObject *type);
static PyObject *t_measureunit_createLux(PyTypeObject *type);
static PyObject *t_measureunit_createMegabit(PyTypeObject *type);
static PyObject *t_measureunit_createMegabyte(PyTypeObject *type);
static PyObject *t_measureunit_createMegahertz(PyTypeObject *type);
static PyObject *t_measureunit_createMegaliter(PyTypeObject *type);
static PyObject *t_measureunit_createMegawatt(PyTypeObject *type);
static PyObject *t_measureunit_createMeterPerSecondSquared(PyTypeObject *type);
static PyObject *t_measureunit_createMetricTon(PyTypeObject *type);
static PyObject *t_measureunit_createMicrogram(PyTypeObject *type);
static PyObject *t_measureunit_createMicrometer(PyTypeObject *type);
static PyObject *t_measureunit_createMicrosecond(PyTypeObject *type);
static PyObject *t_measureunit_createMilePerGallon(PyTypeObject *type);
static PyObject *t_measureunit_createMilliampere(PyTypeObject *type);
static PyObject *t_measureunit_createMilligram(PyTypeObject *type);
static PyObject *t_measureunit_createMilliliter(PyTypeObject *type);
static PyObject *t_measureunit_createMillimeterOfMercury(PyTypeObject *type);
static PyObject *t_measureunit_createMilliwatt(PyTypeObject *type);
static PyObject *t_measureunit_createNanometer(PyTypeObject *type);
static PyObject *t_measureunit_createNanosecond(PyTypeObject *type);
static PyObject *t_measureunit_createNauticalMile(PyTypeObject *type);
static PyObject *t_measureunit_createOhm(PyTypeObject *type);
static PyObject *t_measureunit_createOunceTroy(PyTypeObject *type);
static PyObject *t_measureunit_createParsec(PyTypeObject *type);
static PyObject *t_measureunit_createPint(PyTypeObject *type);
static PyObject *t_measureunit_createPoundPerSquareInch(PyTypeObject *type);
static PyObject *t_measureunit_createQuart(PyTypeObject *type);
static PyObject *t_measureunit_createRadian(PyTypeObject *type);
static PyObject *t_measureunit_createSquareCentimeter(PyTypeObject *type);
static PyObject *t_measureunit_createSquareInch(PyTypeObject *type);
static PyObject *t_measureunit_createSquareYard(PyTypeObject *type);
static PyObject *t_measureunit_createStone(PyTypeObject *type);
static PyObject *t_measureunit_createTablespoon(PyTypeObject *type);
static PyObject *t_measureunit_createTeaspoon(PyTypeObject *type);
static PyObject *t_measureunit_createTerabit(PyTypeObject *type);
static PyObject *t_measureunit_createTerabyte(PyTypeObject *type);
static PyObject *t_measureunit_createTon(PyTypeObject *type);
static PyObject *t_measureunit_createVolt(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(56, 0, 0)
static PyObject *t_measureunit_createCentury(PyTypeObject *type);
static PyObject *t_measureunit_createCupMetric(PyTypeObject *type);
static PyObject *t_measureunit_createGenericTemperature(PyTypeObject *type);
static PyObject *t_measureunit_createKnot(PyTypeObject *type);
static PyObject *t_measureunit_createLiterPer100Kilometers(PyTypeObject *type);
static PyObject *t_measureunit_createMileScandinavian(PyTypeObject *type);
static PyObject *t_measureunit_createPintMetric(PyTypeObject *type);
static PyObject *t_measureunit_createRevolutionAngle(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(57, 0, 0)
static PyObject *t_measureunit_createGallonImperial(PyTypeObject *type);
static PyObject *t_measureunit_createMilePerGallonImperial(PyTypeObject *type);
static PyObject *t_measureunit_createMilligramPerDeciliter(PyTypeObject *type);
static PyObject *t_measureunit_createMillimolePerLiter(PyTypeObject *type);
static PyObject *t_measureunit_createPartPerMillion(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(59, 0, 0)
static PyObject *t_measureunit_createPoint(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(63, 0, 0)
static PyObject *t_measureunit_createAtmosphere(PyTypeObject *type);
static PyObject *t_measureunit_createPercent(PyTypeObject *type);
static PyObject *t_measureunit_createPermille(PyTypeObject *type);
static PyObject *t_measureunit_createPetabyte(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(64, 0, 0)
static PyObject *t_measureunit_createBarrel(PyTypeObject *type);
static PyObject *t_measureunit_createBritishThermalUnit(PyTypeObject *type);
static PyObject *t_measureunit_createDalton(PyTypeObject *type);
static PyObject *t_measureunit_createDayPerson(PyTypeObject *type);
static PyObject *t_measureunit_createDunam(PyTypeObject *type);
static PyObject *t_measureunit_createEarthMass(PyTypeObject *type);
static PyObject *t_measureunit_createElectronvolt(PyTypeObject *type);
static PyObject *t_measureunit_createFluidOunceImperial(PyTypeObject *type);
static PyObject *t_measureunit_createKilopascal(PyTypeObject *type);
static PyObject *t_measureunit_createMegapascal(PyTypeObject *type);
static PyObject *t_measureunit_createMole(PyTypeObject *type);
static PyObject *t_measureunit_createMonthPerson(PyTypeObject *type);
static PyObject *t_measureunit_createNewton(PyTypeObject *type);
static PyObject *t_measureunit_createNewtonMeter(PyTypeObject *type);
static PyObject *t_measureunit_createPermyriad(PyTypeObject *type);
static PyObject *t_measureunit_createPoundFoot(PyTypeObject *type);
static PyObject *t_measureunit_createPoundForce(PyTypeObject *type);
static PyObject *t_measureunit_createSolarLuminosity(PyTypeObject *type);
static PyObject *t_measureunit_createSolarMass(PyTypeObject *type);
static PyObject *t_measureunit_createSolarRadius(PyTypeObject *type);
static PyObject *t_measureunit_createWeekPerson(PyTypeObject *type);
static PyObject *t_measureunit_createYearPerson(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(65, 0, 0)
static PyObject *t_measureunit_createBar(PyTypeObject *type);
static PyObject *t_measureunit_createDecade(PyTypeObject *type);
static PyObject *t_measureunit_createDotPerCentimeter(PyTypeObject *type);
static PyObject *t_measureunit_createDotPerInch(PyTypeObject *type);
static PyObject *t_measureunit_createEm(PyTypeObject *type);
static PyObject *t_measureunit_createMegapixel(PyTypeObject *type);
static PyObject *t_measureunit_createPascal(PyTypeObject *type);
static PyObject *t_measureunit_createPixel(PyTypeObject *type);
static PyObject *t_measureunit_createPixelPerCentimeter(PyTypeObject *type);
static PyObject *t_measureunit_createPixelPerInch(PyTypeObject *type);
static PyObject *t_measureunit_createThermUs(PyTypeObject *type);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(68, 0, 0)
static PyObject *t_measureunit_createCandela(PyTypeObject *type);
static PyObject *t_measureunit_createDessertSpoon(PyTypeObject *type);
static PyObject *t_measureunit_createDessertSpoonImperial(PyTypeObject *type);
static PyObject *t_measureunit_createDot(PyTypeObject *type);
static PyObject *t_measureunit_createDram(PyTypeObject *type);
static PyObject *t_measureunit_createDrop(PyTypeObject *type);
static PyObject *t_measureunit_createEarthRadius(PyTypeObject *type);
static PyObject *t_measureunit_createGrain(PyTypeObject *type);
static PyObject *t_measureunit_createJigger(PyTypeObject *type);
static PyObject *t_measureunit_createLumen(PyTypeObject *type);
static PyObject *t_measureunit_createPinch(PyTypeObject *type);
static PyObject *t_measureunit_createQuartImperial(PyTypeObject *type);
#endif

static PyMethodDef t_measureunit_methods[] = {
#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
    DECLARE_METHOD(t_measureunit, getType, METH_NOARGS),
    DECLARE_METHOD(t_measureunit, getSubtype, METH_NOARGS),
    DECLARE_METHOD(t_measureunit, getAvailable, METH_O | METH_CLASS),
    DECLARE_METHOD(t_measureunit, getAvailableTypes, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(67, 0, 0)
    DECLARE_METHOD(t_measureunit, getIdentifier, METH_NOARGS),
    DECLARE_METHOD(t_measureunit, getComplexity, METH_NOARGS),
#endif
    
#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
    DECLARE_METHOD(t_measureunit, createAcre, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createArcMinute, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createArcSecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCelsius, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCentimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicKilometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicMile, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDay, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDegree, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFahrenheit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFoot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGForce, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGram, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHectare, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHectopascal, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHorsepower, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHour, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createInch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createInchHg, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilogram, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilometerPerHour, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilowatt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLightYear, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLiter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMeterPerSecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMile, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilePerHour, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMillibar, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMillimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMillisecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMinute, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMonth, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createOunce, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPicometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPound, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareFoot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareKilometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareMeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareMile, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createWatt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createWeek, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createYard, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createYear, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)
    DECLARE_METHOD(t_measureunit, createAcreFoot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createAmpere, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createAstronomicalUnit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createBit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createBushel, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createByte, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCalorie, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCarat, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCentiliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicCentimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicFoot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicInch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicMeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCubicYard, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCup, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDeciliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDecimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFathom, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFluidOunce, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFoodcalorie, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFurlong, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGallon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGigabit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGigabyte, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGigahertz, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGigawatt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHectoliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createHertz, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createJoule, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKarat, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKelvin, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilobit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilobyte, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilocalorie, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilohertz, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilojoule, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilowattHour, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLiterPerKilometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLux, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegabit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegabyte, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegahertz, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegaliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegawatt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMeterPerSecondSquared, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMetricTon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMicrogram, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMicrometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMicrosecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilePerGallon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilliampere, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilligram, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilliliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMillimeterOfMercury, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilliwatt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createNanometer, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createNanosecond, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createNauticalMile, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createOhm, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createOunceTroy, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createParsec, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPint, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPoundPerSquareInch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createQuart, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createRadian, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareCentimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareInch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSquareYard, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createStone, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createTablespoon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createTeaspoon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createTerabit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createTerabyte, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createTon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createVolt, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(56, 0, 0)
    DECLARE_METHOD(t_measureunit, createCentury, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createCupMetric, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGenericTemperature, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKnot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLiterPer100Kilometers, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMileScandinavian, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPintMetric, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createRevolutionAngle, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(57, 0, 0)
    DECLARE_METHOD(t_measureunit, createGallonImperial, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilePerGallonImperial, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMilligramPerDeciliter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMillimolePerLiter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPartPerMillion, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(59, 0, 0)
    DECLARE_METHOD(t_measureunit, createPoint, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(63, 0, 0)
    DECLARE_METHOD(t_measureunit, createAtmosphere, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPercent, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPermille, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPetabyte, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(64, 0, 0)
    DECLARE_METHOD(t_measureunit, createBarrel, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createBritishThermalUnit, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDalton, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDayPerson, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDunam, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createEarthMass, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createElectronvolt, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createFluidOunceImperial, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createKilopascal, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegapascal, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMole, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMonthPerson, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createNewton, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createNewtonMeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPermyriad, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPoundFoot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPoundForce, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSolarLuminosity, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSolarMass, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createSolarRadius, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createWeekPerson, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createYearPerson, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(65, 0, 0)
    DECLARE_METHOD(t_measureunit, createBar, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDecade, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDotPerCentimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDotPerInch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createEm, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createMegapixel, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPascal, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPixel, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPixelPerCentimeter, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPixelPerInch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createThermUs, METH_NOARGS | METH_CLASS),
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(68, 0, 0)
    DECLARE_METHOD(t_measureunit, createCandela, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDessertSpoon, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDessertSpoonImperial, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDot, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDram, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createDrop, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createEarthRadius, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createGrain, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createJigger, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createLumen, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createPinch, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_measureunit, createQuartImperial, METH_NOARGS | METH_CLASS),
#endif
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(MeasureUnit, t_measureunit, UObject, MeasureUnit,
             abstract_init, NULL)


/* Measure */

class t_measure : public _wrapper {
public:
    Measure *object;
};

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 1, 0)
static int t_measure_init(t_measure *self, PyObject *args, PyObject *kwds);
#endif
static PyObject *t_measure_getNumber(t_measure *self);
static PyObject *t_measure_getUnit(t_measure *self);

static PyMethodDef t_measure_methods[] = {
    DECLARE_METHOD(t_measure, getNumber, METH_NOARGS),
    DECLARE_METHOD(t_measure, getUnit, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 1, 0)
DECLARE_TYPE(Measure, t_measure, UObject, Measure, t_measure_init, NULL)
#else
DECLARE_TYPE(Measure, t_measure, UObject, Measure, abstract_init, NULL)
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)

/* NoUnit */

#if U_ICU_VERSION_HEX < VERSION_HEX(68, 0, 0)
using NoUnit_ = NoUnit;
#else
using NoUnit_ = MeasureUnit;
#endif

class t_nounit : public _wrapper {
public:
    NoUnit_ *object;
};

static PyObject *t_nounit_base(PyTypeObject *type);
static PyObject *t_nounit_percent(PyTypeObject *type);
static PyObject *t_nounit_permille(PyTypeObject *type);

static PyMethodDef t_nounit_methods[] = {
    DECLARE_METHOD(t_nounit, base, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_nounit, percent, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_nounit, permille, METH_NOARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(NoUnit, t_nounit, MeasureUnit, NoUnit_,
             abstract_init, NULL)

#endif


/* CurrencyUnit */

class t_currencyunit : public _wrapper {
public:
    CurrencyUnit *object;
};

static int t_currencyunit_init(t_currencyunit *self,
                               PyObject *args, PyObject *kwds);
static PyObject *t_currencyunit_getISOCurrency(t_currencyunit *self);

static PyMethodDef t_currencyunit_methods[] = {
    DECLARE_METHOD(t_currencyunit, getISOCurrency, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CurrencyUnit, t_currencyunit, MeasureUnit, CurrencyUnit,
             t_currencyunit_init, NULL)


/* CurrencyAmount */

class t_currencyamount : public _wrapper {
public:
    CurrencyAmount *object;
};

static int t_currencyamount_init(t_currencyamount *self,
                                 PyObject *args, PyObject *kwds);
static PyObject *t_currencyamount_getCurrency(t_currencyamount *self);
static PyObject *t_currencyamount_getISOCurrency(t_currencyamount *self);

static PyMethodDef t_currencyamount_methods[] = {
    DECLARE_METHOD(t_currencyamount, getCurrency, METH_NOARGS),
    DECLARE_METHOD(t_currencyamount, getISOCurrency, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CurrencyAmount, t_currencyamount, Measure, CurrencyAmount,
             t_currencyamount_init, NULL)


/* TimeUnit */

#if U_ICU_VERSION_HEX >= 0x04020000

class t_timeunit : public _wrapper {
public:
    TimeUnit *object;
};

static PyObject *t_timeunit_getTimeUnitField(t_timeunit *self);
static PyObject *t_timeunit_createInstance(PyTypeObject *type, PyObject *arg);

static PyMethodDef t_timeunit_methods[] = {
    DECLARE_METHOD(t_timeunit, getTimeUnitField, METH_NOARGS),
    DECLARE_METHOD(t_timeunit, createInstance, METH_O | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(TimeUnit, t_timeunit, MeasureUnit, TimeUnit,
             abstract_init, NULL)


/* TimeUnitAmount */

class t_timeunitamount : public _wrapper {
public:
    TimeUnitAmount *object;
};

static int t_timeunitamount_init(t_timeunitamount *self, PyObject *args,
                                 PyObject *kwds);
static PyObject *t_timeunitamount_getUnit(t_timeunitamount *self);
static PyObject *t_timeunitamount_getTimeUnitField(t_timeunitamount *self);

static PyMethodDef t_timeunitamount_methods[] = {
    DECLARE_METHOD(t_timeunitamount, getUnit, METH_NOARGS),
    DECLARE_METHOD(t_timeunitamount, getTimeUnitField, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(TimeUnitAmount, t_timeunitamount, Measure, TimeUnitAmount,
             t_timeunitamount_init, NULL)

#endif


/* MeasureUnit */

DEFINE_RICHCMP(MeasureUnit, t_measureunit)


#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)

static PyObject *t_measureunit_str(t_measureunit *self)
{
#if U_ICU_VERSION_HEX >= VERSION_HEX(67, 0, 0)
    return PyString_FromString(self->object->getIdentifier());
#else
    return PyString_FromString(self->object->getSubtype());
#endif
}

static PyObject *t_measureunit_getType(t_measureunit *self)
{
    return PyString_FromString(self->object->getType());
}

static PyObject *t_measureunit_getSubtype(t_measureunit *self)
{
    return PyString_FromString(self->object->getSubtype());
}

static PyObject *t_measureunit_getAvailable(PyTypeObject *type, PyObject *arg)
{
    charsArg type_name;

    if (!parseArg(arg, "n", &type_name))
    {
        UErrorCode status = U_ZERO_ERROR;
        int32_t size = MeasureUnit::getAvailable(type_name, NULL, 0, status);

        if (U_FAILURE(status))
        {
            if (status != U_BUFFER_OVERFLOW_ERROR)
                return ICUException(status).reportError();

            MeasureUnit *mus = new MeasureUnit[size];

            status = U_ZERO_ERROR;
            size = MeasureUnit::getAvailable(type_name, mus, size, status);

            if (U_FAILURE(status))
            {
                delete[] mus;
                return ICUException(status).reportError();
            }

            PyObject *result = PyTuple_New(size);

            for (int i = 0; i < size; ++i)
                PyTuple_SET_ITEM(result, i, wrap_MeasureUnit(
                    (MeasureUnit *) mus[i].clone(), T_OWNED));

            delete[] mus;

            return result;
        }
    }

    return PyErr_SetArgsError(type, "getAvailable", arg);
}

static PyObject *t_measureunit_getAvailableTypes(PyTypeObject *type)
{
    StringEnumeration *e;

    STATUS_CALL(e = MeasureUnit::getAvailableTypes(status));
    return wrap_StringEnumeration(e, T_OWNED);
}

#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(67, 0, 0)

static PyObject *t_measureunit_getIdentifier(t_measureunit *self)
{
    const char *id = self->object->getIdentifier();
    return PyString_FromString(id);                
}

static PyObject *t_measureunit_getComplexity(t_measureunit *self)
{
    UMeasureUnitComplexity complexity;
    STATUS_CALL(complexity = self->object->getComplexity(status));
    return PyInt_FromLong(complexity);                
}

#endif


#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)

#define createMU(unit) \
    static PyObject *t_measureunit_create ## unit(PyTypeObject *type) \
    {                                                                 \
        MeasureUnit *mu;                                              \
        STATUS_CALL(mu = MeasureUnit::create ## unit(status));        \
        return wrap_MeasureUnit(mu, T_OWNED);                         \
    }

createMU(Acre)
createMU(ArcMinute)
createMU(ArcSecond)
createMU(Celsius)
createMU(Centimeter)
createMU(CubicKilometer)
createMU(CubicMile)
createMU(Day)
createMU(Degree)
createMU(Fahrenheit)
createMU(Foot)
createMU(GForce)
createMU(Gram)
createMU(Hectare)
createMU(Hectopascal)
createMU(Horsepower)
createMU(Hour)
createMU(Inch)
createMU(InchHg)
createMU(Kilogram)
createMU(Kilometer)
createMU(KilometerPerHour)
createMU(Kilowatt)
createMU(LightYear)
createMU(Liter)
createMU(Meter)
createMU(MeterPerSecond)
createMU(Mile)
createMU(MilePerHour)
createMU(Millibar)
createMU(Millimeter)
createMU(Millisecond)
createMU(Minute)
createMU(Month)
createMU(Ounce)
createMU(Picometer)
createMU(Pound)
createMU(Second)
createMU(SquareFoot)
createMU(SquareKilometer)
createMU(SquareMeter)
createMU(SquareMile)
createMU(Watt)
createMU(Week)
createMU(Yard)
createMU(Year)
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)
createMU(AcreFoot)
createMU(Ampere)
createMU(AstronomicalUnit)
createMU(Bit)
createMU(Bushel)
createMU(Byte)
createMU(Calorie)
createMU(Carat)
createMU(Centiliter)
createMU(CubicCentimeter)
createMU(CubicFoot)
createMU(CubicInch)
createMU(CubicMeter)
createMU(CubicYard)
createMU(Cup)
createMU(Deciliter)
createMU(Decimeter)
createMU(Fathom)
createMU(FluidOunce)
createMU(Foodcalorie)
createMU(Furlong)
createMU(Gallon)
createMU(Gigabit)
createMU(Gigabyte)
createMU(Gigahertz)
createMU(Gigawatt)
createMU(Hectoliter)
createMU(Hertz)
createMU(Joule)
createMU(Karat)
createMU(Kelvin)
createMU(Kilobit)
createMU(Kilobyte)
createMU(Kilocalorie)
createMU(Kilohertz)
createMU(Kilojoule)
createMU(KilowattHour)
createMU(LiterPerKilometer)
createMU(Lux)
createMU(Megabit)
createMU(Megabyte)
createMU(Megahertz)
createMU(Megaliter)
createMU(Megawatt)
createMU(MeterPerSecondSquared)
createMU(MetricTon)
createMU(Microgram)
createMU(Micrometer)
createMU(Microsecond)
createMU(MilePerGallon)
createMU(Milliampere)
createMU(Milligram)
createMU(Milliliter)
createMU(MillimeterOfMercury)
createMU(Milliwatt)
createMU(Nanometer)
createMU(Nanosecond)
createMU(NauticalMile)
createMU(Ohm)
createMU(OunceTroy)
createMU(Parsec)
createMU(Pint)
createMU(PoundPerSquareInch)
createMU(Quart)
createMU(Radian)
createMU(SquareCentimeter)
createMU(SquareInch)
createMU(SquareYard)
createMU(Stone)
createMU(Tablespoon)
createMU(Teaspoon)
createMU(Terabit)
createMU(Terabyte)
createMU(Ton)
createMU(Volt)
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(56, 0, 0)
createMU(Century)
createMU(CupMetric)
createMU(GenericTemperature)
createMU(Knot)
createMU(LiterPer100Kilometers)
createMU(MileScandinavian)
createMU(PintMetric)
createMU(RevolutionAngle)
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(57, 0, 0)
createMU(GallonImperial)
createMU(MilePerGallonImperial)
createMU(MilligramPerDeciliter)
createMU(MillimolePerLiter)
createMU(PartPerMillion)
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(59, 0, 0)
createMU(Point)
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(63, 0, 0)
createMU(Atmosphere)
createMU(Percent)
createMU(Permille)
createMU(Petabyte)
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(64, 0, 0)
createMU(Barrel)
createMU(BritishThermalUnit)
createMU(Dalton)
createMU(DayPerson)
createMU(Dunam)
createMU(EarthMass)
createMU(Electronvolt)
createMU(FluidOunceImperial)
createMU(Kilopascal)
createMU(Megapascal)
createMU(Mole)
createMU(MonthPerson)
createMU(Newton)
createMU(NewtonMeter)
createMU(Permyriad)
createMU(PoundFoot)
createMU(PoundForce)
createMU(SolarLuminosity)
createMU(SolarMass)
createMU(SolarRadius)
createMU(WeekPerson)
createMU(YearPerson)
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(65, 0, 0)
createMU(Bar)
createMU(Decade)
createMU(DotPerCentimeter)
createMU(DotPerInch)
createMU(Em)
createMU(Megapixel)
createMU(Pascal)
createMU(Pixel)
createMU(PixelPerCentimeter)
createMU(PixelPerInch)
createMU(ThermUs)
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(68, 0, 0)
createMU(Candela)
createMU(DessertSpoon)
createMU(DessertSpoonImperial)
createMU(Dot)
createMU(Dram)
createMU(Drop)
createMU(EarthRadius)
createMU(Grain)
createMU(Jigger)
createMU(Lumen)
createMU(Pinch)
createMU(QuartImperial)
#endif

/* Measure */

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 1, 0)

static int t_measure_init(t_measure *self, PyObject *args, PyObject *kwds)
{
    Formattable *number;
    MeasureUnit *unit;
    double d;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "dP", TYPE_ID(MeasureUnit), &d, &unit))
        {
            INT_STATUS_CALL(self->object = new Measure(
                Formattable(d), (MeasureUnit *) unit->clone(), status));
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "PP", TYPE_CLASSID(Formattable),
                       TYPE_ID(MeasureUnit), &number, &unit))
        {
            INT_STATUS_CALL(self->object = new Measure(
                *number, (MeasureUnit *) unit->clone(), status));
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;

      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }

    if (self->object)
        return 0;

    return -1;
}

#endif

static PyObject *t_measure_getNumber(t_measure *self)
{
    Formattable *f = new Formattable(self->object->getNumber());
    return wrap_Formattable(f, T_OWNED);
}

static PyObject *t_measure_getUnit(t_measure *self)
{
    MeasureUnit *u = (MeasureUnit *) self->object->getUnit().clone();
    return wrap_MeasureUnit(u, T_OWNED);
}

static PyObject *t_measure_str(t_measure *self)
{
#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)
    UnicodeString u;

// this conditional is wider than necessary because of
// www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4296.pdf#section.16.3
// and to placate the msvc++ compiler
#if U_ICU_VERSION_HEX >= VERSION_HEX(64, 0, 0)
    STATUS_CALL(u = icu::number::NumberFormatter::withLocale(
        Locale::getDefault())
                .unit(self->object->getUnit())
                .unitWidth(UNumberUnitWidth::UNUM_UNIT_WIDTH_FULL_NAME)
                .formatDouble(self->object->getNumber().getDouble(), status)
                .toString(status));
#else
    STATUS_CALL(u = icu::number::NumberFormatter::withLocale(
        Locale::getDefault())
                .unit(self->object->getUnit())
                .unitWidth(UNumberUnitWidth::UNUM_UNIT_WIDTH_FULL_NAME)
                .formatDouble(self->object->getNumber().getDouble(), status)
                .toString());
#endif

    return PyUnicode_FromUnicodeString(&u);
#else
    PyObject *value = wrap_Formattable(const_cast<Formattable *>(&self->object->getNumber()), 0);
    PyObject *unit = wrap_MeasureUnit(const_cast<MeasureUnit *>(&self->object->getUnit()), 0);
    PyObject *v_str = PyObject_Str(value);
    PyObject *u_str = PyObject_Str(unit);
    PyObject *args = PyTuple_Pack(2, v_str, u_str);
    PyObject *format = PyString_FromString("%s %s");
    PyObject *str = PyString_Format(format, args);

    Py_DECREF(format);
    Py_DECREF(args);
    Py_DECREF(u_str);
    Py_DECREF(v_str);
    Py_DECREF(unit);
    Py_DECREF(value);

    return str;
#endif
}

DEFINE_RICHCMP(Measure, t_measure)


/* NoUnit */

#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)

static PyObject *t_nounit_base(PyTypeObject *type)
{
  return wrap_NoUnit((NoUnit_ *) NoUnit::base().clone(), T_OWNED);
}

static PyObject *t_nounit_percent(PyTypeObject *type)
{
    return wrap_NoUnit((NoUnit_ *) NoUnit::percent().clone(), T_OWNED);
}

static PyObject *t_nounit_permille(PyTypeObject *type)
{
    return wrap_NoUnit((NoUnit_ *) NoUnit::permille().clone(), T_OWNED);
}

#endif


/* CurrencyUnit */

static int t_currencyunit_init(t_currencyunit *self,
                               PyObject *args, PyObject *kwds)
{
    UErrorCode status = U_ZERO_ERROR;
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArgs(args, "S", &u, &_u))
    {
        CurrencyUnit *cu = new CurrencyUnit(u->getTerminatedBuffer(), status);

        if (U_FAILURE(status))
        {
            ICUException(status).reportError();
            return -1;
        }

        self->object = cu;
        self->flags = T_OWNED;

        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}

static PyObject *t_currencyunit_getISOCurrency(t_currencyunit *self)
{
    UnicodeString u(self->object->getISOCurrency());
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_currencyunit_str(t_currencyunit *self)
{
    UnicodeString u(self->object->getISOCurrency());
    return PyUnicode_FromUnicodeString(&u);
}


/* CurrencyAmount */

static int t_currencyamount_init(t_currencyamount *self,
                                 PyObject *args, PyObject *kwds)
{
    UErrorCode status = U_ZERO_ERROR;
    Formattable *f;
    double d;
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArgs(args, "PS", TYPE_CLASSID(Formattable),
                   &f, &u, &_u))
    {
        CurrencyAmount *ca =
            new CurrencyAmount(*f, u->getTerminatedBuffer(), status);

        if (U_FAILURE(status))
        {
            ICUException(status).reportError();
            return -1;
        }

        self->object = ca;
        self->flags = T_OWNED;

        return 0;
    }

    if (!parseArgs(args, "dS", &d, &u, &_u))
    {
        CurrencyAmount *ca =
            new CurrencyAmount(d, u->getTerminatedBuffer(), status);

        if (U_FAILURE(status))
        {
            ICUException(status).reportError();
            return -1;
        }

        self->object = ca;
        self->flags = T_OWNED;

        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}

static PyObject *t_currencyamount_getCurrency(t_currencyamount *self)
{
    CurrencyUnit *cu = new CurrencyUnit(self->object->getCurrency());
    return wrap_CurrencyUnit(cu, T_OWNED);
}

static PyObject *t_currencyamount_getISOCurrency(t_currencyamount *self)
{
    UnicodeString u(self->object->getISOCurrency());
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_currencyamount_str(t_currencyamount *self)
{
    UnicodeString u(self->object->getISOCurrency());
    UErrorCode status = U_ZERO_ERROR;
    double d = self->object->getNumber().getDouble(status);

    PyObject *currency = PyUnicode_FromUnicodeString(&u);
    PyObject *amount = PyFloat_FromDouble(d);
    PyObject *format = PyString_FromString("%s %0.2f");
    PyObject *tuple = PyTuple_New(2);
    PyObject *str;

    PyTuple_SET_ITEM(tuple, 0, currency);
    PyTuple_SET_ITEM(tuple, 1, amount);
    str = PyString_Format(format, tuple);
    Py_DECREF(tuple);
    Py_DECREF(format);

    return str;
}


/* TimeUnit */

#if U_ICU_VERSION_HEX >= 0x04020000

static PyObject *t_timeunit_getTimeUnitField(t_timeunit *self)
{
    return PyInt_FromLong(self->object->getTimeUnitField());
}

static PyObject *t_timeunit_createInstance(PyTypeObject *type, PyObject *arg)
{
    TimeUnit::UTimeUnitFields field;

    if (!parseArg(arg, "i", &field))
    {
        TimeUnit *tu;
        STATUS_CALL(tu = TimeUnit::createInstance(field, status));

        return wrap_TimeUnit(tu, T_OWNED);
    }

    return PyErr_SetArgsError(type, "getAvailable", arg);
}


/* TimeUnitAmount */

static int t_timeunitamount_init(t_timeunitamount *self, PyObject *args,
                                 PyObject *kwds)
{
    Formattable *obj;
    TimeUnit::UTimeUnitFields field;
    double d;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "Pi", TYPE_CLASSID(Formattable), &obj, &field))
        {
            INT_STATUS_CALL(self->object = new TimeUnitAmount(
                *obj, field, status));
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "di", &d, &field))
        {
            INT_STATUS_CALL(self->object = new TimeUnitAmount(
                d, field, status));
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;

      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }

    if (self->object)
        return 0;

    return -1;
}

static PyObject *t_timeunitamount_getUnit(t_timeunitamount *self)
{
    return wrap_TimeUnit(
        (TimeUnit *) self->object->getTimeUnit().clone(), T_OWNED);
}

static PyObject *t_timeunitamount_getTimeUnitField(t_timeunitamount *self)
{
    return PyInt_FromLong(self->object->getTimeUnitField());
}

#endif

void _init_measureunit(PyObject *m)
{
#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
    MeasureUnitType_.tp_str = (reprfunc) t_measureunit_str;
#endif
    MeasureUnitType_.tp_richcompare = (richcmpfunc) t_measureunit_richcmp;
    MeasureType_.tp_richcompare = (richcmpfunc) t_measure_richcmp;
    CurrencyUnitType_.tp_str = (reprfunc) t_currencyunit_str;
    CurrencyAmountType_.tp_str = (reprfunc) t_currencyamount_str;
    MeasureType_.tp_str = (reprfunc) t_measure_str;

#if U_ICU_VERSION_HEX >= 0x04020000
    INSTALL_CONSTANTS_TYPE(UTimeUnitFields, m);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(67, 0, 0)
    INSTALL_CONSTANTS_TYPE(UMeasureUnitComplexity, m);
#endif

    INSTALL_TYPE(MeasureUnit, m);
    INSTALL_TYPE(Measure, m);
#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)
#if U_ICU_VERSION_HEX < VERSION_HEX(68, 0, 0)
    REGISTER_TYPE(NoUnit, m);
#else
    INSTALL_STRUCT(NoUnit, m);
#endif
#endif
    REGISTER_TYPE(CurrencyUnit, m);
    REGISTER_TYPE(CurrencyAmount, m);
#if U_ICU_VERSION_HEX >= 0x04020000
    REGISTER_TYPE(TimeUnit, m);
    REGISTER_TYPE(TimeUnitAmount, m);
#endif

#if U_ICU_VERSION_HEX >= 0x04020000
    INSTALL_ENUM(UTimeUnitFields, "YEAR", TimeUnit::UTIMEUNIT_YEAR);
    INSTALL_ENUM(UTimeUnitFields, "MONTH", TimeUnit::UTIMEUNIT_MONTH);
    INSTALL_ENUM(UTimeUnitFields, "DAY", TimeUnit::UTIMEUNIT_DAY);
    INSTALL_ENUM(UTimeUnitFields, "WEEK", TimeUnit::UTIMEUNIT_WEEK);
    INSTALL_ENUM(UTimeUnitFields, "HOUR", TimeUnit::UTIMEUNIT_HOUR);
    INSTALL_ENUM(UTimeUnitFields, "MINUTE", TimeUnit::UTIMEUNIT_MINUTE);
    INSTALL_ENUM(UTimeUnitFields, "SECOND", TimeUnit::UTIMEUNIT_SECOND);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(67, 0, 0)
    INSTALL_ENUM(UMeasureUnitComplexity, "SINGLE", UMEASURE_UNIT_SINGLE);
    INSTALL_ENUM(UMeasureUnitComplexity, "COMPOUND", UMEASURE_UNIT_COMPOUND);
    INSTALL_ENUM(UMeasureUnitComplexity, "MIXED", UMEASURE_UNIT_MIXED);
#endif    
}
