#ifndef FUNCTIONS_H
#define FUNCTIONS_H

std::string TextToBinaryString(std::string word);

void sigma0(std::uint32_t* v);

void sigma1(std::uint32_t* v);

std::uint32_t capsigma0(const std::uint32_t v);

std::uint32_t capsigma1(const std::uint32_t v);

std::uint32_t choice(std::uint32_t* x, std::uint32_t* y, std::uint32_t* z);

std::uint32_t majority(std::uint32_t* x, std::uint32_t* y, std::uint32_t* z);

#endif