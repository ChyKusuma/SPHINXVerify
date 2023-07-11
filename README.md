# SPHINXVerify

## Introduction

This project is dedicated to the world community as an Open-source Post-quantum blockchain layer 1 project, means anyone can join and contribute based on his/ her passion and skills. SPHINX is a blockchain protocol designed to provide secure and scalable solutions in the post-quantum era.

This repository contains code for the SPHINXVerify project, which is a `Verify` module scheme for the SPHINX blockchain framework.

## Components

The provided code is using the ZK-STARK (Zero-Knowledge Succinct Non-Interactive Argument of Knowledge) protocol for verification purposes. ZK-STARK is a cryptographic protocol that enables the prover to convince the verifier about the correctness of a statement without revealing any information beyond the validity of the statement.

ZK-STARK offers significant benefits compared to multi-signature schemes in terms of privacy and security.

Privacy: ZK-STARK allows users to prove the validity of transactions without revealing any sensitive information, such as private keys. In contrast, multi-signature schemes typically require the involvement of multiple parties and the exposure of their public keys, which can potentially be used to link transactions and compromise privacy.

Efficiency: ZK-STARK provides succinct non-interactive proofs, meaning that the proof size remains fixed regardless of the complexity of the statement being proven. This efficiency allows for faster and more scalable verification compared to multi-signature schemes, which often require multiple signatures and larger data structures to store the public keys of involved parties.

Trustlessness: ZK-STARK provides a high level of trustlessness as it eliminates the need for trust in the verification process. The validity of a transaction can be mathematically proven using the ZK-STARK proof, without relying on the trustworthiness of specific parties or intermediaries. In multi-signature schemes, trust is placed on the participating entities to sign transactions correctly and honestly.

Security: ZK-STARK offers strong cryptographic security guarantees. It relies on the assumption that the underlying cryptographic primitives, such as hash functions and digital signatures, are secure. In contrast, multi-signature schemes may be susceptible to attacks targeting the key management infrastructure or compromising the security of individual private keys.

In summary, the usage of ZK-STARK in the provided code enhances the privacy, efficiency, trustlessness, and security of transaction broadcasting compared to multi-signature schemes. It enables users to prove transaction validity without revealing sensitive information and provides a robust cryptographic foundation for secure and private blockchain transactions.


### SPHINXVerify Namespace

The `SPHINXVerify` namespace contains functions for verifying SPHINX blocks and chains, performing data verification, and simulating the interaction between a prover and a verifier using the SPHINX protocol.

##### `verifySPHINXBlock(block, signature, public_key)` Verifies the signature of a SPHINX block.

- `block`: A `SPHINXBlock` object representing the block to be verified.
- `signature`: A string containing the signature of the block.
- `public_key`: A `SPHINX_PublicKey` object representing the public key used for verification.

Returns a boolean value indicating whether the signature is valid.

##### `verifySPHINXChain(chain)` Verifies the integrity of a SPHINX chain.

- `chain`: A `SPHINX_Chain` object representing the chain to be verified.

Returns a boolean value indicating whether the chain is valid. The function performs the following verifications:
- Verifies the signature of each block in the chain using `verifySPHINXBlock`.
- Checks if the blocks are properly linked together.

##### `verify_data(data, signature, verifier_public_key)` Verifies data using a signature and public key.

- `data`: A vector of `uint8_t` representing the data to be verified.
- `signature`: A string containing the signature of the data.
- `verifier_public_key`: A vector of `uint8_t` representing the public key used for verification.

Returns a boolean value indicating whether the data is valid.

##### `verify_sphinx_protocol()` Simulates the interaction between a SPHINX prover and verifier using the SPHINX protocol.

Returns a boolean value indicating the final result of the simulation. The function performs the following steps:
- Creates instances of `SPHINXProver` and `SPHINXVerifier` objects.
- Initiates the interaction by obtaining the initial message using `sendMessage` from the verifier object.
- Continues the interaction until the verifier is done by:
  - The prover receives the message from the verifier using `receiveMessage`.
  - The prover sends the response message using `sendMessage`.
  - The response message is passed back to the verifier using `receiveMessage`.
- Verifies the final result using `verify` from the verifier object.

The code provides functions to verify SPHINX blocks and chains, perform data verification, and simulate the interaction between a prover and a verifier using the SPHINX protocol. These functions utilize the capabilities of the `libstark::Protocols::ProverInterface` and `libstark::Protocols::verifierInterface` objects to generate and verify proofs, allowing for secure and private verification of transactions in a blockchain system.


### Note

Every code in the repository is a part of the SPHINX blockchain algorithm, which is currently in development and not fully integrated or extensively tested for functionality. The purpose of this repository is to provide a framework and algorithm for the digital signature scheme in the SPHINX blockchain project.

As the project progresses, further updates and enhancements will be made to ensure the code's stability and reliability. We encourage contributors to participate in improving and refining the SPHINXBlock algorithm by submitting pull requests and providing valuable insights.

We appreciate your understanding and look forward to collaborative efforts in shaping the future of the SPHINX blockchain projec, to accelerating the construction you can find the SPHINCS+ specification here [SPHINCS+](https://github.com/SPHINX-HUB-ORG/SPHINXSign/blob/main/sphincs%2B-round3-specification.pdf).


## Getting Started
To get started with the SPHINX blockchain project, follow the instructions below:

1. Clone the repository: `git clone https://github.com/ChyKusuma/SPHINXVerify.git`
2. Install the necessary dependencies (List the dependencies or provide a link to the installation guide).
3. Explore the codebase to understand the project structure and components.
4. Run the project or make modifications as needed.


## Contributing
We welcome contributions from the developer community to enhance the SPHINX blockchain project. If you are interested in contributing, please follow the guidelines below:

1. Fork the repository on GitHub.
2. Create a new branch for your feature or bug fix: `git checkout -b feature/your-feature-name` or `git checkout -b bugfix/your-bug-fix`.
3. Make your modifications and ensure the code remains clean and readable.
4. Write tests to cover the changes you've made, if applicable.
5. Commit your changes: `git commit -m "Description of your changes"`.
6. Push the branch to your forked repository: `git push origin your-branch-name`.
7. Open a pull request against the main repository, describing your changes and the problem it solves.
8. Insert your information (i.e name, email) in the authors space.

## License
Specify the license under which the project is distributed (MIT License).

## Contact
If you have any questions, suggestions, or feedback regarding the SPHINX blockchain project, feel free to reach out to us at [sphinxfounders@gmail.com](mailto:sphinxfounders@gmail.com).
