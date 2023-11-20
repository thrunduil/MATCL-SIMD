/*
 *  This file is a part of MATCL-SIMD Library
 *
 *  Copyright (c) Pawel Kowal 2017 - 2023
 *
 *  This file is distributed under the BSD License. See LICENSE.txt for details.
 */

#pragma once

#include "matcl-simd/details/math/impl/simd_exp.h"

#ifdef MATCL_SIMD_GENERATE_TABLES
    #include "matcl-mp/matcl_mp.h"
#endif

#include <iomanip>

namespace matcl { namespace simd { namespace details
{

//-------------------------------------------------------------------
//                          exp_table_double
//-------------------------------------------------------------------
#ifdef MATCL_SIMD_GENERATE_TABLES

void exp_table_double::generate_lookup_table(std::ostream& os, int num_values_in_row)
{
    static const int L2 = L/2;
    //double * table    = new double[2*L2 + 1];
    //table             = table + L2;

    precision prec      = precision(53 * 2);
    precision prec_print= precision(20);
    mp_float L_tick     = mp_float(1.0 / L, prec) * constants::mp_ln2(prec);        

    int pos             = 0;
    for (int l = -L2; l <= L2; ++l)
    {
        mp_float x      = mp_float(l, prec) * L_tick;
        x               = exp(x, prec);

        os << std::setw(26);
        os << x.to_string(prec_print);
        ++pos;

        if (pos == num_values_in_row)
        {
            os << ",\n";
            pos = 0;
        }
        else
        {
            os << ", ";
        }
    }

    return;
};

#endif

double exp_table_double::lookup_table_arr[] = {
  0.7071067811865475244,  0.70902394216020759892,   0.7109463010845827799,   0.7128738720527471534,
 0.71480666919598500562,  0.71674470668389442126,   0.7186879987244911628,  0.72063655956431283136,
 0.72259040348852331002,  0.72454954482101749026,  0.72651399792452628242,  0.72848377720072191082,
 0.73045889709032349433,   0.7324393720732029133,  0.73442521666849096343,  0.73641644543468379751,
 0.73841307296974965569,  0.74041511391123588523,  0.74242258293637625027,  0.74443549476219853269,
  0.7464538641456324246,  0.74847770588361771339,  0.75050703481321276013,  0.75254186581170327204,
 0.75458221379671136988,   0.7566280937263049511,   0.7586795205991073494,  0.76073650945440729176,
 0.76279907537226915343,  0.76486723347364351194,   0.7669409989204780009,  0.76902038691582846422,
 0.77110541270397041181,  0.77319609157051077743,  0.77529243884249997956,  0.77739446988854428606,
 0.77950220011891848352,  0.78161564498567885207,  0.78373481998277644653,  0.78585974064617068462,
 0.78799042255394324323,   0.7901268813264122634,  0.79226913262624686506,  0.79441719215858197212,
 0.79657107567113344897,  0.79873079895431354913,   0.8008963778413466769,  0.80306782820838546285,
 0.80524516597462715409,  0.80742840710243032004,  0.80961756759743187465,   0.8118126635086644159,
 0.81401371092867388342,  0.81622072599363753517,  0.81843372488348224388,  0.82065272382200311435,
 0.82287773907698242226,  0.82510878696030887548,  0.82734588382809719879,   0.8295890460808080427,
 0.83183829016336821752,  0.83409363256529125333,  0.83635508982079828681,   0.8386226785089392759,
 0.84089641525371454303,  0.84317631672419664796,  0.84546239963465259099,  0.84775468074466634749,
 0.85005317685926173475,  0.85235790482902561184,  0.85466888155023141355,   0.8569861239649630193,
 0.85930964906123895781,  0.86163947387313694861,  0.86397561548091878112,  0.86631809101115553244,
  0.8686669176368531245,  0.87102211257757822173,  0.87338369309958447004,  0.87575167651593907805,
 0.87812608018664974156,  0.88050692151879191208,  0.88289421796663641052,  0.88528798703177738677,
 0.88768824626326062628,  0.89009501325771220448,  0.89250830565946749007,    0.894928141160700498,
 0.89735453750155359321,  0.89978751247026754603,  0.90222708390331194015,  0.90467326968551593427,
 0.90712608775019937812,  0.90958555607930428415,   0.9120516927035266555,  0.91452451570244867155,
 0.91700404320467123174,  0.91949029338794685886,  0.92198328447931296253,  0.92448303475522546419,
  0.9269895625416927842,  0.92950288621441019231,   0.9320230241988945224,  0.93454999497061925244,
 0.93708381705514995066,  0.93962450902828008902,  0.94217208951616722484,  0.94472657719546955173,
 0.94728799079348282067,  0.94985634908827763236,  0.95243167090883710183,  0.95501397513519489622,
 0.95760328069857364694,  0.96019960658152373695,  0.96280297181806246448,  0.96541339549381358395,
  0.9680308967461472253,  0.97065549476432019261,  0.97328720878961664317,  0.97592605811548914796,
 0.97857206208770013451,  0.98122524010446371338,  0.98388561161658788906,  0.98655319612761715647,
 0.98922801319397548413,  0.99191008242510968493,  0.99459942348363317565,  0.99729605608547012626,
                      1,   1.0027112750502024854,   1.0054299011128028214,   1.0081558981184175158,
    1.01088928605170046,   1.0136300849514894388,   1.0163783149109530379,   1.0191339960777379497,
  1.0218971486541166782,   1.0246677928971356451,   1.0274459491187636965,   1.0302316376860410129,
  1.0330248790212284225,     1.03582569360195712,   1.0386341019613787906,   1.0414501246883161413,
  1.0442737824274138403,   1.0471050958792898661,   1.0499440858006872661,   1.0527907730046263271,
  1.0556451783605571588,   1.0585073227945126901,    1.061377227289262081,   1.0642549128844645498,
  1.0671404006768236182,   1.0700337118202417735,   1.0729348675259755514,   1.0758438890627910378,
  1.0787607977571197937,   1.0816856149932152019,   1.0846183622133092378,   1.0875590609177696653,
  1.0905077326652576592,   1.0934643990728858542,   1.0964290818163768234,   1.0994018026302219855,
  1.1023825833078409436,   1.1053714457017412556,    1.108368411723678638,   1.1113735033448176039,
  1.1143867425958925363,   1.1174081515673691991,   1.1204377524096066844,   1.1234755673330198007,
  1.1265216186082418998,    1.129575928566288146,    1.132638519598719228,   1.1357094141578055142,
  1.1387886347566916537,   1.1418762039695616227,   1.1449721444318042194,   1.1480764788401790068,
  1.1511892299529827058,   1.1543104205902160395,   1.1574400736337510296,   1.1605782120274987464,
  1.1637248587775775138,   1.1668800369524815706,   1.1700437696832501881,   1.1732160801636372475,
  1.1763969916502812763,   1.1795865274628759455,   1.1827847109843410299,   1.1859915656609938314,
  1.1892071150027210667,   1.1924313825831512221,   1.1956643920398273746,   1.1989061670743804818,
  1.2021567314527031421,   1.2054161090051238256,   1.2086843236265815774,   1.2119613992768011945,
  1.2152473599804688781,   1.2185422298274083618,   1.2218460329727575169,   1.2251587936371454377,
  1.2284805361068700057,   1.2318112847340759359,   1.2351510639369333057,   1.2384998981998165678,
  1.2418578120734840486,   1.2452248301752579328,   1.2486009771892047366,   1.2519862778663162701,
  1.2553807570246910896,   1.2587844395497164431,    1.262197350394250708,   1.2656195145788063242,
  1.2690509571917332226,   1.2724917033894027512,   1.2759417783963921004,   1.2794012075056692269,
  1.2828700160787782807,   1.2863482295460255336,   1.2898358734066658122,   1.2933329732290894367,
  1.2968395546510096659,    1.300355643379650651,   1.3038812651919358986,   1.3074164459346772448,
  1.3109612115247643419,   1.3145155879493546585,   1.3180796012660639947,   1.3216532776031575143,
  1.3252366431597412946,   1.3288297242059543955,   1.3324325470831614494,   1.3360451382041457734,
  1.3396675240533030054,   1.3432997311868352638,   1.3469417862329458358,   1.3505937158920343914,
  1.3542555469368927283,   1.3579273062129010465,   1.3616090206382247556,   1.3653007172040118154,
  1.3690024229745906119,   1.3727141650876683693,   1.3764359707545301002,   1.3801678672602380956,
  1.3839098819638319549,    1.387662042298529159,   1.3914243757719261871,   1.3951969099662001783,
  1.3989796725383111402,   1.4027726912202047064,   1.4065759938190154425,   1.4103896082172707044,
  1.4142135623730950488,
};

double* exp_table_double::lookup_table = lookup_table_arr + exp_table_double::L/2;

const float exp_table_float::exp_poly[6] =
{
    1.000000010627969261079092395130339e+00f,
    4.999999812480395306960342830781873e-01f,
    1.666650621954377493093332051884339e-01f,
    4.166713620577822464861187854099253e-02f,
    8.369068563162737202515194738801366e-03f,
    1.388887298908941589713690426191312e-03f,
};

const double exp_table_double::exp_poly[4] =
{
    9.999999999999965009454977779701013e-01,
    5.000000000000029158791378197294776e-01,
    1.666666819398565427110017699653142e-01,
    4.166666666666664815314859891569042e-02,
};

}}}
