//
// Created by Chi Keen Tan on 24/03/2021.
//

#pragma once

// Contains some global config variables

namespace cgsw::config{

    // Keygenerator
    inline constexpr uint32_t g_cgsw1_modulus_constant {3};

    // Constructor (matrix.cpp)
    inline constexpr double g_gaussian_stddev {0.5};
    // TODO:- how to calculate the standard deviation?
    //TODO:- temperorary setting stddev to 0 meaning no noise

}


///
//| Encryption parameters :
//|   scheme: CGSW, PVW variant
//|   security level (k): 2
//|   depth (d): 3
//|   rate (1-epsilon): 0.5
//|   plaintext modulus (p): 1048583
//|   ciphertext modulus (q): 33554737
//|   lattice dimension (n0, n1): 10, 12
//|   second lattice dimension (m): 312
//|   l_p: 21
//|   l_q: 26
//|   f: 32
//\

//message matrix, m =
// [[469708 21927 440044 345598 393624 751853 1015664 1026439 477866 58604]
//[677981 93464 385337 253295 543271 363779 357593 204899 485667 799265]
//[944154 93413 1017633 851519 575031 206045 677571 10461 383849 913158]
//[644215 475248 213879 436217 176540 506435 870973 90881 262971 321600]
//[120038 95049 98959 353010 509018 216197 744760 522599 659383 622842]
//[627325 300428 140254 16277 9894 907955 496591 549935 841357 102688]
//[1025450 443704 13716 305686 280881 90506 479714 26549 839660 367146]
//[899007 549025 584225 431500 280787 672803 988161 507610 885446 231685]
//[913764 766123 851753 748656 415124 295449 331532 696724 658066 441643]
//[637136 313795 800386 693914 609012 751334 29962 104727 829469 497124]


//Decrypted message:
//[[469758 21977 440093 345647 393672 751901 1015714 1026487 477915 58654]
//[678030 93513 385386 253345 543318 363828 357643 204948 485716 799315]
//[944194 93454 1017671 851559 575070 206084 677611 10500 383890 913198]
//[644265 475297 213927 436268 176589 506485 871022 90931 263020 321650]
//[120079 95087 98999 353050 509058 216236 744800 522639 659422 622881]
//[627357 300460 140287 16310 9926 907988 496623 549971 841390 102721]
//[1025514 443766 13779 305748 280943 90568 479777 26613 839721 367207]
//[899056 549073 584273 431548 280834 672852 988209 507660 885494 231734]
//[913812 766172 851802 748705 415173 295497 331581 696774 658113 441692]
//[637166 313825 800415 693943 609041 751364 29992 104756 829499 497154]
//]

