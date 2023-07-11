/*
 *  Copyright (c) (2023) SPHINX_ORG
 *  Authors:
 *    - (C kusuma) <thekoesoemo@gmail.com>
 *      GitHub: (https://github.com/chykusuma)
 *  Contributors:
 *    - (Contributor 1) <email1@example.com>
 *      Github: (https://github.com/yourgit)
 *    - (Contributor 2) <email2@example.com>
 *      Github: (https://github.com/yourgit)
 */


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// The code is a header file that defines a namespace SPHINXVerify containing functions for verifying SPHINX blocks and chains using a protocol library called "Protocol.hpp" based on ZK-STARK.

  // The code starts with an include guard #ifndef VERIFY_HPP and ends with #endif // VERIFY_HPP. This ensures that the header file is included only once during compilation.

  // The necessary header files are included using #include directives. These include "Sign.hpp", "Chain.hpp", "Block.hpp", and the external library "Protocol.hpp" from the "Libstark/src/protocols" directory.

  // The code defines a namespace SPHINXVerify to encapsulate the verification functions.

  // The function verifySPHINXBlock takes a SPHINXBlock object, a signature (string), and a SPHINX_PublicKey object as input. It verifies the signature of the block using the provided signature and public key by calling SPHINXSign::verify_data. The result of the verification is returned as a boolean value.

  // The function verifySPHINXChain takes a SPHINX_Chain object as input. It first retrieves the length of the chain using the getChainLength method. If the chain is empty (length == 0), it considers it valid and returns true. Otherwise, it iterates over each block in the chain and performs the following verifications:

  // It verifies the signature of the current block by calling verifySPHINXBlock with the current block, its signature, and public key. If the block's signature is invalid, it returns false.

  // For each block except the first block, it checks if the PreviousHash of the current block matches the hash of the previous block. If the blocks are not properly linked together, it returns false.

  // If all verifications pass, it indicates that all blocks have been verified, and the chain is considered valid. In that case, it returns true.

  // The function verify_data takes the data to be verified (as a vector of uint8_t), a signature (string), and a verifier's public key (as a vector of uint8_t) as input. Inside the function, it calls the verify function from the sphincs_inner namespace in the external protocol library, passing the data, signature, and verifier's public key. The verify function performs the verification using the ZK-STARK protocol and returns a boolean value indicating the result of the verification.

// This code provides functions to verify the integrity and authenticity of SPHINX blocks and chains using the ZK-STARK protocol through the external library "Protocol.hpp". It utilizes the SPHINXSign class for block signature verification and relies on the provided SPHINX_Chain, SPHINXBlock, and SPHINX_PublicKey classes for block and chain information.
/////////////////////////////////////////////////////////////////////////////////////////////////////////



#ifndef VERIFY_HPP
#define VERIFY_HPP

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Lib/Sphincs/include/sphincs_inner.hpp"
#include "Lib/Libstark/src/protocols/protocol.hpp"
#include "Consensus/Contract.hpp"
#include "Sign.hpp"
#include "Chain.hpp"
#include "Block.hpp"


namespace SPHINXVerify {

    bool verifySPHINXBlock(const SPHINXBlock& block, const std::string& signature, const SPHINX_PublicKey& public_key) {
        // Verify the signature of the block using the provided signature and public key
        bool verified = Crypto::verify(block.getBlockHash(), signature, public_key);
        return verified;
    }

    bool verifySPHINXChain(const SPHINX_Chain& chain) {
        size_t chainLength = chain.getChainLength();

        if (chainLength == 0) {
            // An empty chain is considered valid
            return true;
        }

        // Verify the integrity of each block in the chain
        for (size_t i = 0; i < chainLength; ++i) {
            const SPHINXBlock& currentBlock = chain.getBlockAt(i);

            // Verify the signature of the current block
            bool blockVerified = verifySPHINXBlock(currentBlock, currentBlock.getSignature(), currentBlock.getPublicKey());
            if (!blockVerified) {
                // Invalid block detected
                return false;
            }

            if (i > 0) {
                const SPHINXBlock& previousBlock = chain.getBlockAt(i - 1);
                if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
                    // The blocks are not properly linked together
                    return false;
                }
            }
        }

        // All blocks have been verified and the chain is valid
        return true;
    }

    bool verify_data(const std::vector<uint8_t>& data, const std::string& signature, const std::vector<uint8_t>& verifier_public_key) {
        bool valid = Crypto::verify(data, signature, verifier_public_key);
        return valid;
    }

    bool verify_sphinx_protocol() {
        // Create a SPHINXProver and SPHINXVerifier objects
        SPHINXProver prover;
        SPHINXVerifier verifier;

        // Call the sendMessage function from the verifier object to get the initial message
        libstark::Protocols::msg_ptr_t initialMessage = verifier.sendMessage();

        // Create a TranscriptMessage pointer and assign the initial message
        std::unique_ptr<libstark::Protocols::TranscriptMessage> msg = std::move(initialMessage);

        // Continue the interaction until the verifier is done
        while (!verifier.doneInteracting()) {
            // Send the message to the prover
            prover.receiveMessage(*msg);

            // Call the sendMessage function from the prover to get the response message
            libstark::Protocols::msg_ptr_t responseMessage = prover.sendMessage();

            // Move the response message to the TranscriptMessage pointer
            msg = std::move(responseMessage);

            // Send the message to the verifier
            verifier.receiveMessage(*msg);
        }

        // Verify the final result
        bool valid = verifier.verify();

        return valid;
    }
} // namespace SPHINXVerify

#endif // SPHINX_VERIFY_HPP