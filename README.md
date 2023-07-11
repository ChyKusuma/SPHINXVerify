# SPHINXVerify

## Introduction

This project is dedicated to the world community as an Open-source Post-quantum blockchain layer 1 project, means anyone can join and contribute based on his/ her passion and skills. SPHINX is a blockchain protocol designed to provide secure and scalable solutions in the post-quantum era.

This repository contains code for the SPHINXSign project, which is a `Verify` module for the SPHINX blockchain framework.

## Components

The provided code is using the ZK-STARK (Zero-Knowledge Succinct Non-Interactive Argument of Knowledge) protocol for verification purposes. ZK-STARK is a cryptographic protocol that enables the prover to convince the verifier about the correctness of a statement without revealing any information beyond the validity of the statement.

In the context of the code, ZK-STARK is used to verify the integrity and authenticity of SPHINX blocks and chains. The ZK-STARK protocol ensures that the blocks have not been tampered with and that they are linked together correctly.

Here are the reasons why ZK-STARK is chosen for verification:

1. Security: ZK-STARK provides strong security guarantees. It ensures that the verification process is secure and resistant to attacks such as tampering with block data or forging signatures.

2. Efficiency: ZK-STARK is designed to be efficient and provide succinct proofs. It allows for efficient verification of large amounts of data with minimal computational overhead.

3. Non-Interactivity: ZK-STARK is a non-interactive protocol, meaning that the prover and verifier only need to exchange a fixed number of messages to complete the verification. This property simplifies the verification process and reduces the communication overhead.

4. Zero-Knowledge Property: ZK-STARK guarantees zero-knowledge property, which means that the verification process does not reveal any additional information about the data being verified. It ensures that the confidentiality of sensitive information is maintained during the verification process.

By leveraging the ZK-STARK protocol, the code achieves a high level of security and efficiency in verifying SPHINX blocks and chains, ensuring the integrity and authenticity of the data.

#### SPHINXVerify Namespace

The `SPHINXVerify` namespace encapsulates verification functions for SPHINX blocks and chains.

#### `verifySPHINXBlock(block, signature, public_key)`

Verifies the signature of a SPHINX block.

- `block`: A `SPHINXBlock` object representing the block to be verified.
- `signature`: A string containing the signature of the block.
- `public_key`: A `SPHINX_PublicKey` object representing the public key used for verification.

Returns a boolean value indicating whether the signature is valid.

#### `verifySPHINXChain(chain)`

Verifies the integrity of a SPHINX chain.

- `chain`: A `SPHINX_Chain` object representing the chain to be verified.

Returns a boolean value indicating whether the chain is valid. The function performs the following verifications:
- Verifies the signature of each block in the chain using `verifySPHINXBlock`.
- Checks if the blocks are properly linked together.

#### `verify_data(data, signature, verifier_public_key)`

Verifies data using a signature and public key.

- `data`: A vector of `uint8_t` representing the data to be verified.
- `signature`: A string containing the signature of the data.
- `verifier_public_key`: A vector of `uint8_t` representing the public key used for verification.

Returns a boolean value indicating whether the data is valid.

#### `verify_sphinx_protocol()`

Simulates the interaction between a SPHINXProver and a SPHINXVerifier object.

Returns a boolean value indicating the final result of the simulation. The function performs the following steps:
- Creates instances of `SPHINXProver` and `SPHINXVerifier`.
- Initiates the interaction by obtaining the initial message using `sendMessage` from the verifier object.
- Continues the interaction until the verifier is done interacting:
  - The prover receives the message from the verifier using `receiveMessage`.
  - The prover sends the response message using `sendMessage`.
  - The response message is passed back to the verifier using `receiveMessage`.
- Verifies the final result using `verify` from the verifier object.

## Overall Functionality

The code provides functions to verify SPHINX blocks and chains, perform data verification, and simulate the interaction between a prover and a verifier using the SPHINX protocol.


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
