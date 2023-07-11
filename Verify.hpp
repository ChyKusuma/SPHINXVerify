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
// The provided code defines a namespace SPHINXVerify that contains several functions for verifying the integrity and authenticity of SPHINX blocks and chains, as well as generating and verifying zero-knowledge proofs.

// verifySPHINXBlock function:
  // Parameters: block (SPHINXBlock), signature (string), public_key (SPHINX_PublicKey).
  // This function verifies the signature of a given SPHINX block using the provided signature and public_key.
  // It calls the Crypto::verify function with the block's hash, signature, and public key to perform the verification.
  // Returns true if the signature is valid, false otherwise.

// verifySPHINXChain function:
  // Parameters: chain (SPHINX_Chain).
  // This function verifies the integrity of each block in the provided chain.
  // If the chain is empty (length is 0), it is considered valid and the function returns true.
  // Otherwise, it iterates over each block in the chain and performs the following verifications:
  // Calls verifySPHINXBlock to verify the signature of each block.
  // Checks if the blocks are properly linked together by comparing the previous hash of each block with the hash of the previous block.
  // If any invalid block or improper linkage is detected, the function returns false.
  // If all blocks are verified and the chain is valid, the function returns true.

// verify_data function:
  // Parameters: data (vector of uint8_t), signature (string), verifier_public_key (vector of uint8_t).
  // This function verifies the validity of a data object by performing the following steps:
  // Calls Crypto::verify function with data, signature, and verifier_public_key to check if the signature is valid.
  // If the signature is valid, it proceeds to generate and verify a zero-knowledge proof by using libstark::Protocols::ProverInterface and libstark::Protocols::verifierInterface objects.
  // Creates instances of the prover and verifier parties.
  // Passes the necessary data to the verifier by calling its receiveMessage function with a NecessaryDataMessage object.
  // Generates the proof by calling the sendMessage function from the prover object, which returns a message pointer (proofMessage).
  // Passes the proof message to the verifier by calling its receiveMessage function with the proofMessage.
  // Verifies the proof by calling the verify function from the verifier object.
  // Returns true if the proof is valid, false otherwise.
  // If the initial signature verification fails, the function returns false without generating or verifying the proof.

// verify_sphinx_protocol function:
  // This function demonstrates the interaction between a SPHINXProver and SPHINXVerifier objects to perform a protocol.
  // It creates instances of the prover and verifier.
  // Calls the sendMessage function from the verifier object to get the initial message.
  // Creates a TranscriptMessage pointer and assigns the initial message to it.
  // Continues the interaction between the prover and verifier until the verifier is done (based on doneInteracting).
  // Sends the message to the prover and receives the response message.
  // Moves the response message to the TranscriptMessage pointer.
  // Sends the message to the verifier.
  // Finally, verifies the final result by calling the verify function from the verifier object and returns the result.

// This code utilizes the libstark protocol library and cryptographic techniques to verify SPHINX blocks and chains, as well as generate and verify zero-knowledge proofs.
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

        if (valid) {
            // Create instances of the prover and verifier parties
            libstark::Protocols::ProverInterface prover;
            libstark::Protocols::verifierInterface verifier;

            // Pass the necessary data to the verifier by calling its receiveMessage function
            verifier.receiveMessage(NecessaryDataMessage(data, signature, verifier_public_key));

            // Generate the proof by calling the sendMessage function from the prover object
            libstark::Protocols::msg_ptr_t proofMessage = prover.sendMessage();

            // Pass the proof message to the verifier by calling its receiveMessage function
            verifier.receiveMessage(*proofMessage);

            // Verify the proof by calling the verify function from the verifier object
            bool proofValid = verifier.verify();

            return proofValid;
        }

        return false;
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
