# Compressible FHE


This project, CGSW,  aims to implement the Compressible Fully Homomorphic Scheme (FHE) scheme introduced by Craig Gentry and 
Shai Halevi in 2019 [this paper](https://eprint.iacr.org/2019/733). The paper had described a new additively homomorphic
scheme based on (ring) LWE with a nearly optimal rate (1 - ϵ) and methods to compress several FHE ciphertext into fewer 
high-rate ciphertexts. With this new bandwidth-efficient HE scheme, the publication continued to define a single-server 
private information retrieval (PIR) scheme with low computational overhead, 
making the scheme a practical PIR candidate for large databases. 
These two schemes (Compressible FHE and the new PIR) make case for an interesting implementation and evaluation.

In this project, a total of three schemes will be implemented:

| Schemes                      | Papers | Description                                                                  |
|------------------------------|--------|------------------------------------------------------------------------------|
| GSW                          | GSW13  | The original third-generation FHE scheme based on LWE problem.               |
| PVW-Like Compressed FHE      | GH19   | First of the two variant of compressible FHE schemes devised in paper GH19.  |
| Nearly-square Compressed FHE | GH19   | The second variant of Compressible FHE schemes. (Preferred scheme)           |

Full installation instructions and a list of the required dependencies can be found in [INSTALL.md](INSTALL.md).

For guidance in getting programming with CGSW, take a look at the example programs located in the `examples` directory.

CGSW is written in C++17 and uses the [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) and [NTL](http://www.shoup.net/ntl/) library.

CGSW is distributed under the terms of the [Apache License v2.0](http://www.apache.org/licenses/LICENSE-2.0).

This project is written for Imperial College London Electrical and Electronic as part of MEng EIE Final Year Project.

## Acknowledgements
Being an individual research project, this project has been reusing(learning) styles and structures from 2 of the most 
popular FHE library [HElib](https://github.com/homenc/HElib) and [SEAL](https://github.com/microsoft/SEAL), and hereby 
give credits to these 2 incredibly well-maintained open-source project.
