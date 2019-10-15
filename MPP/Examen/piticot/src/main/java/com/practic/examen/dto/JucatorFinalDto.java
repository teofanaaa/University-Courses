package com.practic.examen.dto;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@AllArgsConstructor
@NoArgsConstructor
@Data
@Builder
public class JucatorFinalDto {
    private String username;
    private String numereGenerate;
    private String pozitii;

}