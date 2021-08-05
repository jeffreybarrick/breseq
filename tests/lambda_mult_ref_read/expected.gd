#=GENOME_DIFF	1.0
#=COMMAND	./src/c/breseq/breseq -j 4 -o tests/lambda_mult_ref_read -r tests/lambda_mult_ref_read/../data/lambda/lambda.1-2.gbk -r tests/lambda_mult_ref_read/../data/lambda/lambda.3.gbk -r tests/lambda_mult_ref_read/../data/lambda/lambda.4.gbk -r tests/lambda_mult_ref_read/../data/lambda/lambda.5.gbk -l 50 tests/lambda_mult_ref_read/../data/lambda/empty.fastq tests/lambda_mult_ref_read/../data/lambda/only_bad.fastq tests/lambda_mult_ref_read/../data/lambda/lambda_mixed_population.1.fastq tests/lambda_mult_ref_read/../data/lambda/lambda_mixed_population.2.fastq tests/lambda_mult_ref_read/../data/lambda/lambda_mixed_population.3.fastq tests/lambda_mult_ref_read/../data/lambda/lambda_mixed_population.4.fastq tests/lambda_mult_ref_read/../data/lambda/lambda_mixed_population.5.fastq
#=REFSEQ	tests/lambda_mult_ref_read/../data/lambda/lambda.1-2.gbk
#=REFSEQ	tests/lambda_mult_ref_read/../data/lambda/lambda.3.gbk
#=REFSEQ	tests/lambda_mult_ref_read/../data/lambda/lambda.4.gbk
#=REFSEQ	tests/lambda_mult_ref_read/../data/lambda/lambda.5.gbk
#=READSEQ	tests/lambda_mult_ref_read/../data/lambda/empty.fastq
#=READSEQ	tests/lambda_mult_ref_read/../data/lambda/only_bad.fastq
#=READSEQ	tests/lambda_mult_ref_read/../data/lambda/lambda_mixed_population.1.fastq
#=READSEQ	tests/lambda_mult_ref_read/../data/lambda/lambda_mixed_population.2.fastq
#=CONVERTED-BASES	2425115
#=CONVERTED-READS	69289
#=INPUT-BASES	2800140
#=INPUT-READS	80004
#=MAPPED-BASES	1783840
#=MAPPED-READS	51266
DEL	1	29	NC_001416-0	139	1	gene_name=–/nu1	gene_position=intergenic (–/-52)	gene_product=–/DNA packaging protein	gene_strand=–/>	locus_tag=–/lambdap01	mutation_category=small_indel	position_end=139	position_start=139	ref_seq=G
INS	2	30	NC_001416-1	4566	G	gene_name=L/K	gene_position=intergenic (+139/-10)	gene_product=tail component/tail component	gene_strand=>/>	genes_promoter=K	locus_tag=lambdap18/lambdap19	locus_tags_promoter=lambdap19	mutation_category=small_indel	position_end=4566	position_start=4566	ref_seq=C
SNP	3	31	NC_001416-2	1261	G	aa_new_seq=E|NA	aa_position=338|NA	aa_ref_seq=K|NA	codon_new_seq=GAA|NA	codon_number=338|NA	codon_position=1|NA	codon_ref_seq=AAA|NA	gene_name=orf-401|orf206b	gene_position=1012|noncoding (107/621 nt)	gene_product=Tail fiber protein|	gene_strand=>|<	genes_overlapping=orf-401,orf206b	locus_tag=lambdap27|lambdap90_made_noncoding	locus_tags_overlapping=lambdap27,lambdap90_made_noncoding	mutation_category=snp_nonsynonymous|noncoding	position_end=1261	position_start=1261	ref_seq=A	snp_type=nonsynonymous|noncoding	transl_table=11|NA
INS	4	32	NC_001416-2	1435	C	gene_name=orf-401	gene_position=coding (1186/1206 nt)	gene_product=Tail fiber protein	gene_strand=>	genes_overlapping=orf-401	locus_tag=lambdap27	locus_tags_overlapping=lambdap27	mutation_category=small_indel	position_end=1435	position_start=1435	ref_seq=C
SNP	5	33	NC_001416-2	2314	A	aa_new_seq=N	aa_position=229	aa_ref_seq=S	codon_new_seq=AAC	codon_number=229	codon_position=2	codon_ref_seq=AGC	gene_name=orf-314	gene_position=686	gene_product=Tail fiber	gene_strand=>	genes_overlapping=orf-314	locus_tag=lambdap28	locus_tags_overlapping=lambdap28	mutation_category=snp_nonsynonymous	position_end=2314	position_start=2314	ref_seq=G	snp_type=nonsynonymous	transl_table=11
DEL	6	60,65	NC_001416-2	2338	5996	gene_name=[orf-314]–ea59	gene_product=[orf-314],orf-194,ea47,ea31,ea59	genes_inactivated=orf-314,orf-194,ea47,ea31,ea59	locus_tag=[lambdap28]–[lambdap82]	locus_tags_inactivated=lambdap28,lambdap29,lambdap80,lambdap81,lambdap82	mutation_category=large_deletion	position_end=8333	position_start=2338	ref_seq=5996-bp
SNP	7	34	NC_001416-3	1915	C	gene_name=orf61|orf63	gene_position=pseudogene (9/186 nt)|noncoding (181/192 nt)	gene_product=hypothetical protein|hypothetical protein	gene_strand=<|<	genes_overlapping=orf61,orf63	locus_tag=lambdap37_made_noncoding|lambdap38_made_noncoding	locus_tags_overlapping=lambdap37_made_noncoding,lambdap38_made_noncoding	mutation_category=snp_pseudogene|noncoding	position_end=1915	position_start=1915	ref_seq=T	snp_type=pseudogene|noncoding
SNP	8	35	NC_001416-3	5833	G	aa_new_seq=G	aa_position=151	aa_ref_seq=G	codon_new_seq=GGG	codon_number=151	codon_position=3	codon_ref_seq=GGA	gene_name=lambdap48	gene_position=453	gene_product=Superinfection exclusion protein B	gene_strand=>	genes_overlapping=lambdap48	locus_tag=lambdap48	locus_tags_overlapping=lambdap48	mutation_category=snp_synonymous	position_end=5833	position_start=5833	ref_seq=A	snp_type=synonymous	transl_table=11
DEL	9	36	NC_001416-3	8717	1	gene_name=cI	gene_position=coding (123/714 nt)	gene_product=repressor	gene_strand=<	genes_inactivated=cI	locus_tag=lambdap88	locus_tags_inactivated=lambdap88	mutation_category=small_indel	position_end=8717	position_start=8717	ref_seq=C
SNP	10	37	NC_001416-4	6817	C	aa_new_seq=F	aa_position=42	aa_ref_seq=F	codon_new_seq=TTC	codon_number=42	codon_position=3	codon_ref_seq=TTT	gene_name=R	gene_position=126	gene_product=endolysin	gene_strand=>	genes_overlapping=R	locus_tag=lambdap75	locus_tags_overlapping=lambdap75	mutation_category=snp_synonymous	position_end=6817	position_start=6817	ref_seq=T	snp_type=synonymous	transl_table=11
INS	11	39	NC_001416-4	8156	A	gene_name=bor/lambdap78	gene_position=intergenic (-205/+85)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	mutation_category=small_indel	position_end=8156	position_start=8156	ref_seq=A
SNP	12	40	NC_001416-4	8184	T	gene_name=bor/lambdap78	gene_position=intergenic (-233/+57)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	mutation_category=snp_intergenic	position_end=8184	position_start=8184	ref_seq=C	snp_type=intergenic
SNP	13	41	NC_001416-4	8191	T	gene_name=bor/lambdap78	gene_position=intergenic (-240/+50)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	mutation_category=snp_intergenic	position_end=8191	position_start=8191	ref_seq=C	snp_type=intergenic
SNP	14	42	NC_001416-4	8203	A	gene_name=bor/lambdap78	gene_position=intergenic (-252/+38)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	mutation_category=snp_intergenic	position_end=8203	position_start=8203	ref_seq=G	snp_type=intergenic
SNP	15	43	NC_001416-4	8328	G	aa_new_seq=H	aa_position=149	aa_ref_seq=H	codon_new_seq=CAC	codon_number=149	codon_position=3	codon_ref_seq=CAT	gene_name=lambdap78	gene_position=447	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_synonymous	position_end=8328	position_start=8328	ref_seq=A	snp_type=synonymous	transl_table=11
SNP	16	44	NC_001416-4	8342	T	aa_new_seq=I	aa_position=145	aa_ref_seq=V	codon_new_seq=ATT	codon_number=145	codon_position=1	codon_ref_seq=GTT	gene_name=lambdap78	gene_position=433	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_nonsynonymous	position_end=8342	position_start=8342	ref_seq=C	snp_type=nonsynonymous	transl_table=11
SNP	17	45	NC_001416-4	8442	A	aa_new_seq=N	aa_position=111	aa_ref_seq=N	codon_new_seq=AAT	codon_number=111	codon_position=3	codon_ref_seq=AAC	gene_name=lambdap78	gene_position=333	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_synonymous	position_end=8442	position_start=8442	ref_seq=G	snp_type=synonymous	transl_table=11
SNP	18	46	NC_001416-4	8514	A	aa_new_seq=I	aa_position=87	aa_ref_seq=I	codon_new_seq=ATT	codon_number=87	codon_position=3	codon_ref_seq=ATC	gene_name=lambdap78	gene_position=261	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_synonymous	position_end=8514	position_start=8514	ref_seq=G	snp_type=synonymous	transl_table=11
SNP	19	47	NC_001416-4	8559	A	aa_new_seq=N	aa_position=72	aa_ref_seq=N	codon_new_seq=AAT	codon_number=72	codon_position=3	codon_ref_seq=AAC	gene_name=lambdap78	gene_position=216	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_synonymous	position_end=8559	position_start=8559	ref_seq=G	snp_type=synonymous	transl_table=11
SNP	20	48	NC_001416-4	8597	T	aa_new_seq=N	aa_position=60	aa_ref_seq=D	codon_new_seq=AAC	codon_number=60	codon_position=1	codon_ref_seq=GAC	gene_name=lambdap78	gene_position=178	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_nonsynonymous	position_end=8597	position_start=8597	ref_seq=C	snp_type=nonsynonymous	transl_table=11
SNP	21	49	NC_001416-4	8708	C	aa_new_seq=A	aa_position=23	aa_ref_seq=T	codon_new_seq=GCG	codon_number=23	codon_position=1	codon_ref_seq=ACG	gene_name=lambdap78	gene_position=67	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_nonsynonymous	position_end=8708	position_start=8708	ref_seq=T	snp_type=nonsynonymous	transl_table=11
SNP	22	50	NC_001416-4	8728	T	aa_new_seq=K	aa_position=16	aa_ref_seq=R	codon_new_seq=AAG	codon_number=16	codon_position=2	codon_ref_seq=AGG	gene_name=lambdap78	gene_position=47	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_nonsynonymous	position_end=8728	position_start=8728	ref_seq=C	snp_type=nonsynonymous	transl_table=11
SNP	23	51	NC_001416-4	8774	A	aa_new_seq=M	aa_position=1	aa_ref_seq=M	codon_new_seq=TTG	codon_number=1	codon_position=1	codon_ref_seq=GTG	gene_name=lambdap78	gene_position=1	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_synonymous	position_end=8774	position_start=8774	ref_seq=C	snp_type=synonymous	transl_table=11
SNP	24	52	NC_001416-4	8868	C	gene_name=lambdap78/lambdap79	gene_position=intergenic (-94/-69)	gene_product=putative envelope protein/hypothetical protein	gene_strand=</>	genes_promoter=lambdap78	locus_tag=lambdap78/lambdap79	locus_tags_promoter=lambdap78	mutation_category=snp_intergenic	position_end=8868	position_start=8868	ref_seq=T	snp_type=intergenic
SNP	25	53	NC_001416-4	9077	G	aa_new_seq=R	aa_position=47	aa_ref_seq=R	codon_new_seq=AGG	codon_number=47	codon_position=3	codon_ref_seq=AGA	gene_name=lambdap79	gene_position=141	gene_product=hypothetical protein	gene_strand=>	genes_overlapping=lambdap79	locus_tag=lambdap79	locus_tags_overlapping=lambdap79	mutation_category=snp_synonymous	position_end=9077	position_start=9077	ref_seq=A	snp_type=synonymous	transl_table=11
SNP	26	54	NC_001416-4	9172	C	gene_name=lambdap79/–	gene_position=intergenic (+29/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	mutation_category=snp_intergenic	position_end=9172	position_start=9172	ref_seq=T	snp_type=intergenic
SUB	27	55,56	NC_001416-4	9176	2	AC	gene_name=lambdap79/–	gene_position=intergenic (+33/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	mutation_category=small_indel	position_end=9177	position_start=9176	ref_seq=GT
SNP	28	57	NC_001416-4	9359	C	gene_name=lambdap79/–	gene_position=intergenic (+216/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	mutation_category=snp_intergenic	position_end=9359	position_start=9359	ref_seq=T	snp_type=intergenic
RA	29	.	NC_001416-0	138	0	G	.	consensus_score=66.5	frequency=1	gene_name=–/nu1	gene_position=intergenic (–/-53)	gene_product=–/DNA packaging protein	gene_strand=–/>	locus_tag=–/lambdap01	major_base=.	major_cov=8/11	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=8/11	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=8/11
RA	30	.	NC_001416-1	4566	1	.	G	consensus_score=66.6	frequency=1	gene_name=L/K	gene_position=intergenic (+139/-10)	gene_product=tail component/tail component	gene_strand=>/>	locus_tag=lambdap18/lambdap19	major_base=G	major_cov=13/13	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=13/13	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=13/13
RA	31	.	NC_001416-2	1261	0	A	G	aa_new_seq=E|NA	aa_position=338|NA	aa_ref_seq=K|NA	codon_new_seq=GAA|NA	codon_number=338|NA	codon_position=1|NA	codon_ref_seq=AAA|NA	consensus_score=66.5	frequency=1	gene_name=orf-401|orf206b	gene_position=1012|noncoding (107/621 nt)	gene_product=Tail fiber protein|	gene_strand=>|<	locus_tag=lambdap27|lambdap90_made_noncoding	major_base=G	major_cov=8/18	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=8/18	new_seq=G	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=A	snp_type=nonsynonymous|noncoding	total_cov=8/18	transl_table=11|NA
RA	32	.	NC_001416-2	1432	1	.	C	aa_new_seq=P	aa_position=395	aa_ref_seq=A	codon_new_seq=CCC	codon_number=395	codon_position=1	codon_ref_seq=GCC	consensus_score=84.6	frequency=1	gene_name=orf-401	gene_position=1183	gene_product=Tail fiber protein	gene_strand=>	locus_tag=lambdap27	major_base=C	major_cov=9/21	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=9/21	new_seq=C	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=G	snp_type=nonsynonymous	total_cov=9/21	transl_table=11
RA	33	.	NC_001416-2	2314	0	G	A	aa_new_seq=N	aa_position=229	aa_ref_seq=S	bias_e_value=48501.9	bias_p_value=0.999998	codon_new_seq=AAC	codon_number=229	codon_position=2	codon_ref_seq=AGC	consensus_score=90.2	fisher_strand_p_value=1	frequency=1	gene_name=orf-314	gene_position=686	gene_product=Tail fiber	gene_strand=>	ks_quality_p_value=0.998219	locus_tag=lambdap28	major_base=A	major_cov=12/21	major_frequency=9.706e-01	minor_base=G	minor_cov=0/1	new_cov=12/21	new_seq=A	polymorphism_frequency=9.706e-01	polymorphism_score=-4.4	prediction=consensus	ref_cov=0/1	ref_seq=G	snp_type=nonsynonymous	total_cov=13/22	transl_table=11
RA	34	.	NC_001416-3	1915	0	T	C	bias_e_value=48502	bias_p_value=1	consensus_score=108.4	fisher_strand_p_value=1	frequency=1	gene_name=orf61|orf63	gene_position=pseudogene (9/186 nt)|noncoding (181/192 nt)	gene_product=hypothetical protein|hypothetical protein	gene_strand=<|<	ks_quality_p_value=1	locus_tag=lambdap37_made_noncoding|lambdap38_made_noncoding	major_base=C	major_cov=25/17	major_frequency=9.767e-01	minor_base=A	minor_cov=1/0	new_cov=25/17	polymorphism_frequency=9.767e-01	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=pseudogene|noncoding	total_cov=26/17
RA	35	.	NC_001416-3	5833	0	A	G	aa_new_seq=G	aa_position=151	aa_ref_seq=G	codon_new_seq=GGG	codon_number=151	codon_position=3	codon_ref_seq=GGA	consensus_score=59.4	frequency=1	gene_name=lambdap48	gene_position=453	gene_product=Superinfection exclusion protein B	gene_strand=>	locus_tag=lambdap48	major_base=G	major_cov=6/19	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=6/19	new_seq=G	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=A	snp_type=synonymous	total_cov=6/19	transl_table=11
RA	36	.	NC_001416-3	8714	0	C	.	consensus_score=71.5	frequency=1	gene_name=cI	gene_position=coding (126/714 nt)	gene_product=repressor	gene_strand=<	locus_tag=lambdap88	major_base=.	major_cov=13/7	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=13/7	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	total_cov=13/7
RA	37	.	NC_001416-4	6817	0	T	C	aa_new_seq=F	aa_position=42	aa_ref_seq=F	bias_e_value=45093	bias_p_value=0.929714	codon_new_seq=TTC	codon_number=42	codon_position=3	codon_ref_seq=TTT	consensus_score=129.4	fisher_strand_p_value=1	frequency=1	gene_name=R	gene_position=126	gene_product=endolysin	gene_strand=>	ks_quality_p_value=0.649315	locus_tag=lambdap75	major_base=C	major_cov=24/25	major_frequency=9.800e-01	minor_base=T	minor_cov=0/1	new_cov=24/25	new_seq=C	polymorphism_frequency=9.800e-01	polymorphism_score=-3.0	prediction=consensus	ref_cov=0/1	ref_seq=T	snp_type=synonymous	total_cov=25/26	transl_table=11
RA	38	.	NC_001416-4	7820	0	A	C	aa_new_seq=S	aa_position=44	aa_ref_seq=S	bias_e_value=22792.1	bias_p_value=0.469921	codon_new_seq=TCG	codon_number=44	codon_position=3	codon_ref_seq=TCT	consensus_reject=FREQUENCY_CUTOFF	consensus_score=71.9	fisher_strand_p_value=1	frequency=2.105e-01	gene_name=bor	gene_position=132	gene_product=Bor protein precursor	gene_strand=<	ks_quality_p_value=0.169261	locus_tag=lambdap77	major_base=A	major_cov=17/13	major_frequency=7.895e-01	minor_base=C	minor_cov=5/3	new_cov=5/3	new_seq=C	polymorphism_frequency=2.105e-01	polymorphism_score=12.5	prediction=polymorphism	ref_cov=17/13	ref_seq=A	snp_type=synonymous	total_cov=22/16	transl_table=11
RA	39	.	NC_001416-4	8152	1	.	A	bias_e_value=47141.3	bias_p_value=0.971946	consensus_score=50.7	fisher_strand_p_value=1	frequency=1	gene_name=bor/lambdap78	gene_position=intergenic (-201/+89)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	ks_quality_p_value=0.772677	locus_tag=lambdap77/lambdap78	major_base=A	major_cov=8/11	major_frequency=9.500e-01	minor_base=.	minor_cov=0/1	new_cov=8/11	polymorphism_frequency=9.500e-01	polymorphism_score=-1.1	prediction=consensus	ref_cov=0/1	snp_type=intergenic	total_cov=8/12
RA	40	.	NC_001416-4	8184	0	C	T	consensus_score=105.0	frequency=1	gene_name=bor/lambdap78	gene_position=intergenic (-233/+57)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	major_base=T	major_cov=21/16	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=21/16	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=21/16
RA	41	.	NC_001416-4	8191	0	C	T	consensus_score=69.9	frequency=1	gene_name=bor/lambdap78	gene_position=intergenic (-240/+50)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	major_base=T	major_cov=12/14	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=12/14	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=12/14
RA	42	.	NC_001416-4	8203	0	G	A	consensus_score=77.1	frequency=1	gene_name=bor/lambdap78	gene_position=intergenic (-252/+38)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	major_base=A	major_cov=12/18	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=12/18	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=12/18
RA	43	.	NC_001416-4	8328	0	A	G	aa_new_seq=H	aa_position=149	aa_ref_seq=H	codon_new_seq=CAC	codon_number=149	codon_position=3	codon_ref_seq=CAT	consensus_score=90.6	frequency=1	gene_name=lambdap78	gene_position=447	gene_product=putative envelope protein	gene_strand=<	locus_tag=lambdap78	major_base=G	major_cov=19/14	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=19/14	new_seq=G	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=A	snp_type=synonymous	total_cov=19/14	transl_table=11
RA	44	.	NC_001416-4	8342	0	C	T	aa_new_seq=I	aa_position=145	aa_ref_seq=V	bias_e_value=48502	bias_p_value=1	codon_new_seq=ATT	codon_number=145	codon_position=1	codon_ref_seq=GTT	consensus_score=85.1	fisher_strand_p_value=1	frequency=1	gene_name=lambdap78	gene_position=433	gene_product=putative envelope protein	gene_strand=<	ks_quality_p_value=1	locus_tag=lambdap78	major_base=T	major_cov=18/13	major_frequency=9.688e-01	minor_base=C	minor_cov=1/0	new_cov=18/13	new_seq=T	polymorphism_frequency=9.688e-01	polymorphism_score=-3.7	prediction=consensus	ref_cov=1/0	ref_seq=C	snp_type=nonsynonymous	total_cov=19/14	transl_table=11
RA	45	.	NC_001416-4	8442	0	G	A	aa_new_seq=N	aa_position=111	aa_ref_seq=N	codon_new_seq=AAT	codon_number=111	codon_position=3	codon_ref_seq=AAC	consensus_score=59.0	frequency=1	gene_name=lambdap78	gene_position=333	gene_product=putative envelope protein	gene_strand=<	locus_tag=lambdap78	major_base=A	major_cov=7/15	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=7/15	new_seq=A	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=G	snp_type=synonymous	total_cov=7/15	transl_table=11
RA	46	.	NC_001416-4	8514	0	G	A	aa_new_seq=I	aa_position=87	aa_ref_seq=I	codon_new_seq=ATT	codon_number=87	codon_position=3	codon_ref_seq=ATC	consensus_score=119.0	frequency=1	gene_name=lambdap78	gene_position=261	gene_product=putative envelope protein	gene_strand=<	locus_tag=lambdap78	major_base=A	major_cov=23/19	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=23/19	new_seq=A	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=G	snp_type=synonymous	total_cov=23/19	transl_table=11
RA	47	.	NC_001416-4	8559	0	G	A	aa_new_seq=N	aa_position=72	aa_ref_seq=N	codon_new_seq=AAT	codon_number=72	codon_position=3	codon_ref_seq=AAC	consensus_score=98.0	frequency=1	gene_name=lambdap78	gene_position=216	gene_product=putative envelope protein	gene_strand=<	locus_tag=lambdap78	major_base=A	major_cov=13/22	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=13/22	new_seq=A	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=G	snp_type=synonymous	total_cov=13/22	transl_table=11
RA	48	.	NC_001416-4	8597	0	C	T	aa_new_seq=N	aa_position=60	aa_ref_seq=D	codon_new_seq=AAC	codon_number=60	codon_position=1	codon_ref_seq=GAC	consensus_score=77.3	frequency=1	gene_name=lambdap78	gene_position=178	gene_product=putative envelope protein	gene_strand=<	locus_tag=lambdap78	major_base=T	major_cov=15/13	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=15/13	new_seq=T	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=C	snp_type=nonsynonymous	total_cov=15/13	transl_table=11
RA	49	.	NC_001416-4	8708	0	T	C	aa_new_seq=A	aa_position=23	aa_ref_seq=T	codon_new_seq=GCG	codon_number=23	codon_position=1	codon_ref_seq=ACG	consensus_score=51.4	frequency=1	gene_name=lambdap78	gene_position=67	gene_product=putative envelope protein	gene_strand=<	locus_tag=lambdap78	major_base=C	major_cov=12/8	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=12/8	new_seq=C	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=T	snp_type=nonsynonymous	total_cov=12/8	transl_table=11
RA	50	.	NC_001416-4	8728	0	C	T	aa_new_seq=K	aa_position=16	aa_ref_seq=R	codon_new_seq=AAG	codon_number=16	codon_position=2	codon_ref_seq=AGG	consensus_score=81.5	frequency=1	gene_name=lambdap78	gene_position=47	gene_product=putative envelope protein	gene_strand=<	locus_tag=lambdap78	major_base=T	major_cov=10/19	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=10/19	new_seq=T	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=C	snp_type=nonsynonymous	total_cov=10/19	transl_table=11
RA	51	.	NC_001416-4	8774	0	C	A	aa_new_seq=M	aa_position=1	aa_ref_seq=M	bias_e_value=38186.6	bias_p_value=0.78732	codon_new_seq=TTG	codon_number=1	codon_position=1	codon_ref_seq=GTG	consensus_score=87.2	fisher_strand_p_value=0.424242	frequency=1	gene_name=lambdap78	gene_position=1	gene_product=putative envelope protein	gene_strand=<	ks_quality_p_value=0.998108	locus_tag=lambdap78	major_base=A	major_cov=13/19	major_frequency=9.697e-01	minor_base=C	minor_cov=1/0	new_cov=13/19	new_seq=A	polymorphism_frequency=9.697e-01	polymorphism_score=NA	prediction=consensus	ref_cov=1/0	ref_seq=C	snp_type=synonymous	total_cov=14/19	transl_table=11
RA	52	.	NC_001416-4	8868	0	T	C	consensus_score=105.8	frequency=1	gene_name=lambdap78/lambdap79	gene_position=intergenic (-94/-69)	gene_product=putative envelope protein/hypothetical protein	gene_strand=</>	locus_tag=lambdap78/lambdap79	major_base=C	major_cov=23/17	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=23/17	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=23/17
RA	53	.	NC_001416-4	9077	0	A	G	aa_new_seq=R	aa_position=47	aa_ref_seq=R	codon_new_seq=AGG	codon_number=47	codon_position=3	codon_ref_seq=AGA	consensus_score=80.2	frequency=1	gene_name=lambdap79	gene_position=141	gene_product=hypothetical protein	gene_strand=>	locus_tag=lambdap79	major_base=G	major_cov=13/18	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=13/18	new_seq=G	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=A	snp_type=synonymous	total_cov=13/18	transl_table=11
RA	54	.	NC_001416-4	9172	0	T	C	consensus_score=97.5	frequency=1	gene_name=lambdap79/–	gene_position=intergenic (+29/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	major_base=C	major_cov=18/19	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=18/19	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=18/19
RA	55	.	NC_001416-4	9176	0	G	A	consensus_score=95.5	frequency=1	gene_name=lambdap79/–	gene_position=intergenic (+33/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	major_base=A	major_cov=18/17	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=18/17	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=18/17
RA	56	.	NC_001416-4	9177	0	T	C	bias_e_value=40570.2	bias_p_value=0.836465	consensus_score=91.4	fisher_strand_p_value=0.485714	frequency=1	gene_name=lambdap79/–	gene_position=intergenic (+34/–)	gene_product=hypothetical protein/–	gene_strand=>/–	ks_quality_p_value=1	locus_tag=lambdap79/–	major_base=C	major_cov=18/16	major_frequency=9.714e-01	minor_base=G	minor_cov=0/1	new_cov=18/16	polymorphism_frequency=9.714e-01	polymorphism_score=-4.3	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=18/17
RA	57	.	NC_001416-4	9359	0	T	C	bias_e_value=42433.8	bias_p_value=0.874889	consensus_score=58.6	fisher_strand_p_value=0.625341	frequency=1	gene_name=lambdap79/–	gene_position=intergenic (+216/–)	gene_product=hypothetical protein/–	gene_strand=>/–	ks_quality_p_value=0.869132	locus_tag=lambdap79/–	major_base=C	major_cov=12/16	major_frequency=8.485e-01	minor_base=T	minor_cov=1/4	new_cov=12/16	polymorphism_frequency=8.485e-01	polymorphism_score=5.9	prediction=consensus	ref_cov=1/4	snp_type=intergenic	total_cov=13/20
RA	58	.	NC_001416-4	9494	0	C	A	bias_e_value=21103.3	bias_p_value=0.435101	consensus_reject=FREQUENCY_CUTOFF	consensus_score=61.3	fisher_strand_p_value=0.25343	frequency=2.250e-01	gene_name=lambdap79/–	gene_position=intergenic (+351/–)	gene_product=hypothetical protein/–	gene_strand=>/–	ks_quality_p_value=0.592988	locus_tag=lambdap79/–	major_base=C	major_cov=19/12	major_frequency=7.750e-01	minor_base=A	minor_cov=3/6	new_cov=3/6	polymorphism_frequency=2.250e-01	polymorphism_score=18.3	prediction=polymorphism	ref_cov=19/12	snp_type=intergenic	total_cov=22/18
MC	59	.	NC_001416-0	1	2	0	0	gene_name=–/nu1	gene_position=intergenic (–/-189)	gene_product=–/DNA packaging protein	gene_strand=–/>	left_inside_cov=0	left_outside_cov=NA	locus_tag=–/lambdap01	right_inside_cov=0	right_outside_cov=49
MC	60	.	NC_001416-2	2338	8333	0	0	gene_name=[orf-314]–ea59	gene_product=[orf-314],orf-194,ea47,ea31,ea59	left_inside_cov=0	left_outside_cov=34	locus_tag=[lambdap28]–[lambdap82]	right_inside_cov=1	right_outside_cov=36
MC	61	.	NC_001416-3	1	13	0	0	gene_name=–/lambdap35	gene_position=intergenic (–/+4)	gene_product=–/hypothetical protein	gene_strand=–/<	left_inside_cov=0	left_outside_cov=NA	locus_tag=–/lambdap35	right_inside_cov=16	right_outside_cov=20
MC	62	.	NC_001416-4	9654	9701	0	0	gene_name=lambdap79/–	gene_position=intergenic (+511/–)	gene_product=hypothetical protein/–	gene_strand=>/–	left_inside_cov=12	left_outside_cov=13	locus_tag=lambdap79/–	right_inside_cov=0	right_outside_cov=NA
JC	63	.	NC_001416-0	9700	-1	NC_001416-1	1	1	0	alignment_overlap=0	coverage_minus=28	coverage_plus=14	flanking_left=35	flanking_right=35	frequency=1	junction_possible_overlap_registers=34	key=NC_001416-0__9700__-1__NC_001416-1__1__1__0____35__35__0__0	max_left=34	max_left_minus=34	max_left_plus=32	max_min_left=17	max_min_left_minus=17	max_min_left_plus=15	max_min_right=16	max_min_right_minus=16	max_min_right_plus=12	max_pos_hash_score=68	max_right=34	max_right_minus=34	max_right_plus=31	neg_log10_pos_hash_p_value=0.1	new_junction_coverage=1.31	new_junction_read_count=46	polymorphism_frequency=1.000e+00	pos_hash_score=29	prediction=consensus	side_1_annotate_key=gene	side_1_continuation=0	side_1_coverage=0.00	side_1_gene_name=V/–	side_1_gene_position=intergenic (+5/–)	side_1_gene_product=tail component/–	side_1_gene_strand=>/–	side_1_locus_tag=lambdap13/–	side_1_overlap=0	side_1_possible_overlap_registers=34	side_1_read_count=0	side_1_redundant=0	side_2_annotate_key=gene	side_2_continuation=0	side_2_coverage=0.00	side_2_gene_name=–/G	side_2_gene_position=intergenic (–/-10)	side_2_gene_product=–/tail component	side_2_gene_strand=–/>	side_2_locus_tag=–/lambdap14	side_2_overlap=0	side_2_possible_overlap_registers=34	side_2_read_count=0	side_2_redundant=0	total_non_overlap_reads=42
JC	64	.	NC_001416-1	9700	-1	NC_001416-2	1	1	0	alignment_overlap=0	coverage_minus=12	coverage_plus=16	flanking_left=35	flanking_right=35	frequency=1	junction_possible_overlap_registers=34	key=NC_001416-1__9700__-1__NC_001416-2__1__1__0____35__35__0__0	max_left=34	max_left_minus=33	max_left_plus=34	max_min_left=16	max_min_left_minus=16	max_min_left_plus=16	max_min_right=17	max_min_right_minus=17	max_min_right_plus=14	max_pos_hash_score=68	max_right=34	max_right_minus=34	max_right_plus=33	neg_log10_pos_hash_p_value=0.0	new_junction_coverage=0.79	new_junction_read_count=29	polymorphism_frequency=1.000e+00	pos_hash_score=21	prediction=consensus	side_1_annotate_key=gene	side_1_continuation=0	side_1_coverage=0.00	side_1_gene_name=lom	side_1_gene_position=coding (436/436 nt)	side_1_gene_product=outer host membrane	side_1_gene_strand=>	side_1_locus_tag=lambdap26	side_1_overlap=0	side_1_possible_overlap_registers=34	side_1_read_count=0	side_1_redundant=0	side_2_annotate_key=gene	side_2_continuation=0	side_2_coverage=0.00	side_2_gene_name=–/orf-401	side_2_gene_position=intergenic (–/-249)	side_2_gene_product=–/Tail fiber protein	side_2_gene_strand=–/>	side_2_locus_tag=–/lambdap27	side_2_overlap=0	side_2_possible_overlap_registers=34	side_2_read_count=0	side_2_redundant=0	total_non_overlap_reads=28
JC	65	.	NC_001416-2	2337	-1	NC_001416-2	8334	1	0	alignment_overlap=5	coverage_minus=10	coverage_plus=11	flanking_left=35	flanking_right=35	frequency=1	junction_possible_overlap_registers=29	key=NC_001416-2__2337__-1__NC_001416-2__8329__1__5____35__35__0__0	max_left=27	max_left_minus=26	max_left_plus=27	max_min_left=9	max_min_left_minus=9	max_min_left_plus=6	max_min_right=15	max_min_right_minus=15	max_min_right_plus=14	max_pos_hash_score=58	max_right=29	max_right_minus=29	max_right_plus=27	neg_log10_pos_hash_p_value=0.0	new_junction_coverage=0.76	new_junction_read_count=25	polymorphism_frequency=9.804e-01	pos_hash_score=16	prediction=consensus	side_1_annotate_key=gene	side_1_continuation=0	side_1_coverage=0.00	side_1_gene_name=orf-314	side_1_gene_position=coding (709/945 nt)	side_1_gene_product=Tail fiber	side_1_gene_strand=>	side_1_locus_tag=lambdap28	side_1_overlap=5	side_1_possible_overlap_registers=34	side_1_read_count=0	side_1_redundant=0	side_2_annotate_key=gene	side_2_continuation=0	side_2_coverage=0.03	side_2_gene_name=ea59/int	side_2_gene_position=intergenic (-761/+78)	side_2_gene_product=ea59/integration protein	side_2_gene_strand=</<	side_2_locus_tag=lambdap82/lambdap33	side_2_overlap=0	side_2_possible_overlap_registers=29	side_2_read_count=1	side_2_redundant=0	total_non_overlap_reads=21
JC	66	.	NC_001416-3	9700	-1	NC_001416-4	1	1	0	alignment_overlap=0	coverage_minus=25	coverage_plus=21	flanking_left=35	flanking_right=35	frequency=1	junction_possible_overlap_registers=34	key=NC_001416-3__9700__-1__NC_001416-4__1__1__0____35__35__0__0	max_left=34	max_left_minus=34	max_left_plus=31	max_min_left=16	max_min_left_minus=16	max_min_left_plus=16	max_min_right=17	max_min_right_minus=17	max_min_right_plus=17	max_pos_hash_score=68	max_right=33	max_right_minus=33	max_right_plus=33	neg_log10_pos_hash_p_value=0.1	new_junction_coverage=1.15	new_junction_read_count=54	polymorphism_frequency=1.000e+00	pos_hash_score=33	prediction=consensus	side_1_annotate_key=gene	side_1_continuation=0	side_1_coverage=0.00	side_1_gene_name=O	side_1_gene_position=coding (116/116 nt)	side_1_gene_product=DNA replication protein	side_1_gene_strand=>	side_1_locus_tag=lambdap89	side_1_overlap=0	side_1_possible_overlap_registers=34	side_1_read_count=0	side_1_redundant=0	side_2_annotate_key=gene	side_2_continuation=0	side_2_coverage=0.00	side_2_gene_name=–/P	side_2_gene_position=intergenic (–/-780)	side_2_gene_product=–/DNA replication protein	side_2_gene_strand=–/>	side_2_locus_tag=–/lambdap61	side_2_overlap=0	side_2_possible_overlap_registers=34	side_2_read_count=0	side_2_redundant=0	total_non_overlap_reads=46
UN	67	.	NC_001416-0	1	8
UN	68	.	NC_001416-0	34	37
UN	69	.	NC_001416-0	8045	8053
UN	70	.	NC_001416-1	4676	4676
UN	71	.	NC_001416-1	5406	5406
UN	72	.	NC_001416-1	7291	7292
UN	73	.	NC_001416-1	7295	7296
UN	74	.	NC_001416-2	2338	8333
UN	75	.	NC_001416-2	9697	9701
UN	76	.	NC_001416-3	1	10
UN	77	.	NC_001416-4	9666	9666
UN	78	.	NC_001416-4	9668	9701
