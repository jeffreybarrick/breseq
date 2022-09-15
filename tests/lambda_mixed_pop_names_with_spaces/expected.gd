#=GENOME_DIFF	1.0
#=TITLE	my_favorite_phage_genome
#=AUTHOR	Arthur C. T. Genome
#=COMMAND	./src/c/breseq/breseq -j 4 -o tests/lambda_mixed_pop_names_with_spaces/output output -g tests/lambda_mixed_pop_names_with_spaces/header.gd --genbank-field-for-seq-id version -r tests/lambda_mixed_pop_names_with_spaces/lambda space.gbk tests/lambda_mixed_pop_names_with_spaces/lambda mixed population space.fastq
#=REFSEQ	location:lambda_mixed_population.fastq
#=READSEQ	location:lambda_mixed_population.fastq
#=CONVERTED-BASES	6998495
#=CONVERTED-READS	199957
#=INPUT-BASES	7000144
#=INPUT-READS	200010
#=MAPPED-BASES	4954413
#=MAPPED-READS	142683
#=ORIGINAL-BASES	536
#=ORIGINAL-READS	100
DEL	1	30	NC_001416.1	139	1	gene_name=–/nu1	gene_position=intergenic (–/-52)	gene_product=–/DNA packaging protein	gene_strand=–/>	locus_tag=–/lambdap01	mutation_category=small_indel	position_end=139	position_start=139	ref_seq=G
INS	2	31	NC_001416.1	14266	G	gene_name=L/K	gene_position=intergenic (+139/-10)	gene_product=tail component/tail component	gene_strand=>/>	genes_promoter=K	locus_tag=lambdap18/lambdap19	locus_tags_promoter=lambdap19	mutation_category=small_indel	position_end=14266	position_start=14266	ref_seq=C
SNP	3	32	NC_001416.1	20661	G	aa_new_seq=E|S	aa_position=338|36	aa_ref_seq=?|?	codon_new_seq=GAA|TCT	codon_number=338|36	codon_position=1|2	codon_ref_seq=NAA|TNT	gene_name=orf-401|orf206b	gene_position=1012|107	gene_product=Tail fiber protein|hypothetical protein	gene_strand=>|<	genes_overlapping=orf-401,orf206b	locus_tag=lambdap27|lambdap90	locus_tags_overlapping=lambdap27,lambdap90	mutation_category=snp_nonsynonymous|nonsynonymous	position_end=20661	position_start=20661	ref_seq=N	snp_type=nonsynonymous|nonsynonymous	transl_table=11|11
INS	4	33	NC_001416.1	20835	C	gene_name=orf-401	gene_position=coding (1186/1206 nt)	gene_product=Tail fiber protein	gene_strand=>	genes_overlapping=orf-401	locus_tag=lambdap27	locus_tags_overlapping=lambdap27	mutation_category=small_indel	position_end=20835	position_start=20835	ref_seq=C
SNP	5	34	NC_001416.1	21714	A	aa_new_seq=N	aa_position=229	aa_ref_seq=S	codon_new_seq=AAC	codon_number=229	codon_position=2	codon_ref_seq=AGC	gene_name=orf-314	gene_position=686	gene_product=Tail fiber	gene_strand=>	genes_overlapping=orf-314	locus_tag=lambdap28	locus_tags_overlapping=lambdap28	mutation_category=snp_nonsynonymous	position_end=21714	position_start=21714	ref_seq=G	snp_type=nonsynonymous	transl_table=11
DEL	6	63,65	NC_001416.1	21738	5996	gene_name=[orf-314]–ea59	gene_product=[orf-314],orf-194,ea47,ea31,ea59	genes_inactivated=orf-314,orf-194,ea47,ea31,ea59	locus_tag=[lambdap28]–[lambdap82]	locus_tags_inactivated=lambdap28,lambdap29,lambdap80,lambdap81,lambdap82	mutation_category=large_deletion	position_end=27733	position_start=21738	ref_seq=5996-bp
SNP	7	35	NC_001416.1	31016	C	aa_new_seq=E|D	aa_position=3|61	aa_ref_seq=E|N	codon_new_seq=GAG|GAC	codon_number=3|61	codon_position=3|1	codon_ref_seq=GAA|AAC	gene_name=orf61|orf63	gene_position=9|181	gene_product=hypothetical protein|hypothetical protein	gene_strand=<|<	genes_overlapping=orf61,orf63	locus_tag=lambdap37|lambdap38	locus_tags_overlapping=lambdap37,lambdap38	mutation_category=snp_synonymous|nonsynonymous	position_end=31016	position_start=31016	ref_seq=T	snp_type=synonymous|nonsynonymous	transl_table=11|11
SNP	8	36	NC_001416.1	34934	G	aa_new_seq=G	aa_position=151	aa_ref_seq=G	codon_new_seq=GGG	codon_number=151	codon_position=3	codon_ref_seq=GGA	gene_name=lambdap48	gene_position=453	gene_product=Superinfection exclusion protein B	gene_strand=>	genes_overlapping=lambdap48	locus_tag=lambdap48	locus_tags_overlapping=lambdap48	mutation_category=snp_synonymous	position_end=34934	position_start=34934	ref_seq=A	snp_type=synonymous	transl_table=11
DEL	9	37	NC_001416.1	37818	1	gene_name=cI	gene_position=coding (123/714 nt)	gene_product=repressor	gene_strand=<	genes_inactivated=cI	locus_tag=lambdap88	locus_tags_inactivated=lambdap88	mutation_category=small_indel	position_end=37818	position_start=37818	ref_seq=C
SNP	10	38	NC_001416.1	45618	C	aa_new_seq=F	aa_position=42	aa_ref_seq=F	codon_new_seq=TTC	codon_number=42	codon_position=3	codon_ref_seq=TTT	gene_name=R	gene_position=126	gene_product=endolysin	gene_strand=>	genes_overlapping=R	locus_tag=lambdap75	locus_tags_overlapping=lambdap75	mutation_category=snp_synonymous	position_end=45618	position_start=45618	ref_seq=T	snp_type=synonymous	transl_table=11
INS	11	42	NC_001416.1	46957	A	gene_name=bor/lambdap78	gene_position=intergenic (-205/+85)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	mutation_category=small_indel	position_end=46957	position_start=46957	ref_seq=A
SNP	12	43	NC_001416.1	46985	T	gene_name=bor/lambdap78	gene_position=intergenic (-233/+57)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	mutation_category=snp_intergenic	position_end=46985	position_start=46985	ref_seq=C	snp_type=intergenic
SNP	13	44	NC_001416.1	46992	T	gene_name=bor/lambdap78	gene_position=intergenic (-240/+50)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	mutation_category=snp_intergenic	position_end=46992	position_start=46992	ref_seq=C	snp_type=intergenic
SNP	14	45	NC_001416.1	47004	A	gene_name=bor/lambdap78	gene_position=intergenic (-252/+38)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	mutation_category=snp_intergenic	position_end=47004	position_start=47004	ref_seq=G	snp_type=intergenic
SNP	15	46	NC_001416.1	47129	G	aa_new_seq=H	aa_position=149	aa_ref_seq=H	codon_new_seq=CAC	codon_number=149	codon_position=3	codon_ref_seq=CAT	gene_name=lambdap78	gene_position=447	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_synonymous	position_end=47129	position_start=47129	ref_seq=A	snp_type=synonymous	transl_table=11
SNP	16	47	NC_001416.1	47143	T	aa_new_seq=I	aa_position=145	aa_ref_seq=V	codon_new_seq=ATT	codon_number=145	codon_position=1	codon_ref_seq=GTT	gene_name=lambdap78	gene_position=433	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_nonsynonymous	position_end=47143	position_start=47143	ref_seq=C	snp_type=nonsynonymous	transl_table=11
SNP	17	48	NC_001416.1	47243	A	aa_new_seq=N	aa_position=111	aa_ref_seq=N	codon_new_seq=AAT	codon_number=111	codon_position=3	codon_ref_seq=AAC	gene_name=lambdap78	gene_position=333	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_synonymous	position_end=47243	position_start=47243	ref_seq=G	snp_type=synonymous	transl_table=11
SNP	18	49	NC_001416.1	47315	A	aa_new_seq=I	aa_position=87	aa_ref_seq=?	codon_new_seq=ATT	codon_number=87	codon_position=3	codon_ref_seq=NTC	gene_name=lambdap78	gene_position=261	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_synonymous	position_end=47315	position_start=47315	ref_seq=G	snp_type=synonymous	transl_table=11
SNP	19	50	NC_001416.1	47317	T	aa_new_seq=I	aa_position=87	aa_ref_seq=?	codon_new_seq=ATT	codon_number=87	codon_position=1	codon_ref_seq=NTC	gene_name=lambdap78	gene_position=259	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_nonsynonymous	position_end=47317	position_start=47317	ref_seq=N	snp_type=nonsynonymous	transl_table=11
SNP	20	51	NC_001416.1	47360	A	aa_new_seq=N	aa_position=72	aa_ref_seq=N	codon_new_seq=AAT	codon_number=72	codon_position=3	codon_ref_seq=AAC	gene_name=lambdap78	gene_position=216	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_synonymous	position_end=47360	position_start=47360	ref_seq=G	snp_type=synonymous	transl_table=11
SNP	21	52	NC_001416.1	47398	T	aa_new_seq=N	aa_position=60	aa_ref_seq=D	codon_new_seq=AAC	codon_number=60	codon_position=1	codon_ref_seq=GAC	gene_name=lambdap78	gene_position=178	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_nonsynonymous	position_end=47398	position_start=47398	ref_seq=C	snp_type=nonsynonymous	transl_table=11
SNP	22	53	NC_001416.1	47509	C	aa_new_seq=A	aa_position=23	aa_ref_seq=T	codon_new_seq=GCG	codon_number=23	codon_position=1	codon_ref_seq=ACG	gene_name=lambdap78	gene_position=67	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_nonsynonymous	position_end=47509	position_start=47509	ref_seq=T	snp_type=nonsynonymous	transl_table=11
SNP	23	54	NC_001416.1	47529	T	aa_new_seq=K	aa_position=16	aa_ref_seq=R	codon_new_seq=AAG	codon_number=16	codon_position=2	codon_ref_seq=AGG	gene_name=lambdap78	gene_position=47	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_nonsynonymous	position_end=47529	position_start=47529	ref_seq=C	snp_type=nonsynonymous	transl_table=11
SNP	24	55	NC_001416.1	47575	A	aa_new_seq=M	aa_position=1	aa_ref_seq=M	codon_new_seq=TTG	codon_number=1	codon_position=1	codon_ref_seq=GTG	gene_name=lambdap78	gene_position=1	gene_product=putative envelope protein	gene_strand=<	genes_overlapping=lambdap78	locus_tag=lambdap78	locus_tags_overlapping=lambdap78	mutation_category=snp_synonymous	position_end=47575	position_start=47575	ref_seq=C	snp_type=synonymous	transl_table=11
SNP	25	56	NC_001416.1	47669	C	gene_name=lambdap78/lambdap79	gene_position=intergenic (-94/-69)	gene_product=putative envelope protein/hypothetical protein	gene_strand=</>	genes_promoter=lambdap78	locus_tag=lambdap78/lambdap79	locus_tags_promoter=lambdap78	mutation_category=snp_intergenic	position_end=47669	position_start=47669	ref_seq=T	snp_type=intergenic
SNP	26	57	NC_001416.1	47878	G	aa_new_seq=R	aa_position=47	aa_ref_seq=R	codon_new_seq=AGG	codon_number=47	codon_position=3	codon_ref_seq=AGA	gene_name=lambdap79	gene_position=141	gene_product=hypothetical protein	gene_strand=>	genes_overlapping=lambdap79	locus_tag=lambdap79	locus_tags_overlapping=lambdap79	mutation_category=snp_synonymous	position_end=47878	position_start=47878	ref_seq=A	snp_type=synonymous	transl_table=11
SNP	27	58	NC_001416.1	47973	C	gene_name=lambdap79/–	gene_position=intergenic (+29/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	mutation_category=snp_intergenic	position_end=47973	position_start=47973	ref_seq=T	snp_type=intergenic
SUB	28	59,60	NC_001416.1	47977	2	AC	gene_name=lambdap79/–	gene_position=intergenic (+33/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	mutation_category=small_indel	position_end=47978	position_start=47977	ref_seq=GT
SNP	29	61	NC_001416.1	48160	C	gene_name=lambdap79/–	gene_position=intergenic (+216/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	mutation_category=snp_intergenic	position_end=48160	position_start=48160	ref_seq=T	snp_type=intergenic
RA	30	.	NC_001416.1	139	0	G	.	consensus_score=278.1	frequency=1	gene_name=–/nu1	gene_position=intergenic (–/-52)	gene_product=–/DNA packaging protein	gene_strand=–/>	locus_tag=–/lambdap01	major_base=.	major_cov=32/39	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=32/39	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=32/39
RA	31	.	NC_001416.1	14266	1	.	G	consensus_score=197.2	frequency=1	gene_name=L/K	gene_position=intergenic (+139/-10)	gene_product=tail component/tail component	gene_strand=>/>	locus_tag=lambdap18/lambdap19	major_base=G	major_cov=43/28	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=43/28	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=43/28
RA	32	.	NC_001416.1	20661	0	N	G	aa_new_seq=E|S	aa_position=338|36	aa_ref_seq=?|?	bias_e_value=42633.8	bias_p_value=0.87901	codon_new_seq=GAA|TCT	codon_number=338|36	codon_position=1|2	codon_ref_seq=NAA|TNT	consensus_score=249.1	fisher_strand_p_value=1	frequency=1	gene_name=orf-401|orf206b	gene_position=1012|107	gene_product=Tail fiber protein|hypothetical protein	gene_strand=>|<	ks_quality_p_value=0.550335	locus_tag=lambdap27|lambdap90	major_base=G	major_cov=26/65	major_frequency=9.891e-01	minor_base=A	minor_cov=0/1	new_cov=26/65	new_seq=G	polymorphism_frequency=9.891e-01	polymorphism_score=-3.3	prediction=consensus	ref_cov=0/0	ref_seq=N	snp_type=nonsynonymous|nonsynonymous	total_cov=26/67	transl_table=11|11
RA	33	.	NC_001416.1	20835	1	.	C	aa_new_seq=?	aa_position=396	aa_ref_seq=H	codon_new_seq=NAC	codon_number=396	codon_position=1	codon_ref_seq=CAC	consensus_score=269.2	frequency=1	gene_name=orf-401	gene_position=1186	gene_product=Tail fiber protein	gene_strand=>	locus_tag=lambdap27	major_base=C	major_cov=32/61	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=32/61	new_seq=N	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=C	snp_type=nonsynonymous	total_cov=32/61	transl_table=11
RA	34	.	NC_001416.1	21714	0	G	A	aa_new_seq=N	aa_position=229	aa_ref_seq=S	bias_e_value=48502	bias_p_value=1	codon_new_seq=AAC	codon_number=229	codon_position=2	codon_ref_seq=AGC	consensus_score=299.0	fisher_strand_p_value=1	frequency=1	gene_name=orf-314	gene_position=686	gene_product=Tail fiber	gene_strand=>	ks_quality_p_value=0.999798	locus_tag=lambdap28	major_base=A	major_cov=35/64	major_frequency=9.900e-01	minor_base=G	minor_cov=0/1	new_cov=35/64	new_seq=A	polymorphism_frequency=9.900e-01	polymorphism_score=NA	prediction=consensus	ref_cov=0/1	ref_seq=G	snp_type=nonsynonymous	total_cov=36/65	transl_table=11
RA	35	.	NC_001416.1	31016	0	T	C	aa_new_seq=E|D	aa_position=3|61	aa_ref_seq=E|N	bias_e_value=48502	bias_p_value=1	codon_new_seq=GAG|GAC	codon_number=3|61	codon_position=3|1	codon_ref_seq=GAA|AAC	consensus_score=279.8	fisher_strand_p_value=1	frequency=1	gene_name=orf61|orf63	gene_position=9|181	gene_product=hypothetical protein|hypothetical protein	gene_strand=<|<	ks_quality_p_value=1	locus_tag=lambdap37|lambdap38	major_base=C	major_cov=55/45	major_frequency=9.901e-01	minor_base=A	minor_cov=1/0	new_cov=55/45	new_seq=C	polymorphism_frequency=9.901e-01	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=T	snp_type=synonymous|nonsynonymous	total_cov=56/45	transl_table=11|11
RA	36	.	NC_001416.1	34934	0	A	G	aa_new_seq=G	aa_position=151	aa_ref_seq=G	bias_e_value=48502	bias_p_value=1	codon_new_seq=GGG	codon_number=151	codon_position=3	codon_ref_seq=GGA	consensus_score=182.2	fisher_strand_p_value=1	frequency=1	gene_name=lambdap48	gene_position=453	gene_product=Superinfection exclusion protein B	gene_strand=>	ks_quality_p_value=1	locus_tag=lambdap48	major_base=G	major_cov=22/44	major_frequency=9.851e-01	minor_base=T	minor_cov=0/1	new_cov=22/44	new_seq=G	polymorphism_frequency=9.851e-01	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=A	snp_type=synonymous	total_cov=22/45	transl_table=11
RA	37	.	NC_001416.1	37818	0	C	.	bias_e_value=48497.2	bias_p_value=0.9999	consensus_score=176.5	fisher_strand_p_value=1	frequency=1	gene_name=cI	gene_position=coding (123/714 nt)	gene_product=repressor	gene_strand=<	ks_quality_p_value=0.985916	locus_tag=lambdap88	major_base=.	major_cov=29/18	major_frequency=9.792e-01	minor_base=C	minor_cov=1/0	new_cov=29/18	polymorphism_frequency=9.792e-01	polymorphism_score=-0.7	prediction=consensus	ref_cov=1/0	total_cov=30/18
RA	38	.	NC_001416.1	45618	0	T	C	aa_new_seq=F	aa_position=42	aa_ref_seq=F	bias_e_value=24681	bias_p_value=0.508866	codon_new_seq=TTC	codon_number=42	codon_position=3	codon_ref_seq=TTT	consensus_score=377.6	fisher_strand_p_value=0.19201	frequency=1	gene_name=R	gene_position=126	gene_product=endolysin	gene_strand=>	ks_quality_p_value=1	locus_tag=lambdap75	major_base=C	major_cov=57/75	major_frequency=9.851e-01	minor_base=A	minor_cov=2/0	new_cov=57/75	new_seq=C	polymorphism_frequency=9.851e-01	polymorphism_score=NA	prediction=consensus	ref_cov=0/1	ref_seq=T	snp_type=synonymous	total_cov=59/76	transl_table=11
RA	39	.	NC_001416.1	46430	0	T	C	bias_e_value=143.149	bias_p_value=0.0029514	consensus_reject=FREQUENCY_CUTOFF	consensus_score=144.1	fisher_strand_p_value=0.000889079	frequency=2.125e-01	gene_name=Rz/bor	gene_position=intergenic (+3/+29)	gene_product=cell lysis protein/Bor protein precursor	gene_strand=>/<	ks_quality_p_value=0.367802	locus_tag=lambdap76/lambdap77	major_base=T	major_cov=27/36	major_frequency=7.875e-01	minor_base=C	minor_cov=15/2	new_cov=15/2	polymorphism_frequency=2.125e-01	polymorphism_score=24.9	prediction=polymorphism	ref_cov=27/36	snp_type=intergenic	total_cov=42/38
RA	40	.	NC_001416.1	46597	0	G	A	aa_new_seq=V	aa_position=52	aa_ref_seq=V	bias_e_value=2400.65	bias_p_value=0.0494959	codon_new_seq=GTT	codon_number=52	codon_position=3	codon_ref_seq=GTC	consensus_reject=FREQUENCY_CUTOFF	consensus_score=123.8	fisher_strand_p_value=0.119269	frequency=2.381e-01	gene_name=bor	gene_position=156	gene_product=Bor protein precursor	gene_strand=<	ks_quality_p_value=0.0720956	locus_tag=lambdap77	major_base=G	major_cov=40/24	major_frequency=7.619e-01	minor_base=A	minor_cov=8/12	new_cov=8/12	new_seq=A	polymorphism_frequency=2.381e-01	polymorphism_score=38.7	prediction=polymorphism	ref_cov=40/24	ref_seq=G	snp_type=synonymous	total_cov=48/37	transl_table=11
RA	41	.	NC_001416.1	46608	0	T	C	aa_new_seq=E	aa_position=49	aa_ref_seq=K	bias_e_value=33062.4	bias_p_value=0.68167	codon_new_seq=GAG	codon_number=49	codon_position=1	codon_ref_seq=AAG	consensus_reject=FREQUENCY_CUTOFF	consensus_score=128.0	fisher_strand_p_value=0.358717	frequency=2.029e-01	gene_name=bor	gene_position=145	gene_product=Bor protein precursor	gene_strand=<	ks_quality_p_value=0.88488	locus_tag=lambdap77	major_base=T	major_cov=36/19	major_frequency=7.971e-01	minor_base=C	minor_cov=7/7	new_cov=7/7	new_seq=C	polymorphism_frequency=2.029e-01	polymorphism_score=21.2	prediction=polymorphism	ref_cov=36/19	ref_seq=T	snp_type=nonsynonymous	total_cov=43/26	transl_table=11
RA	42	.	NC_001416.1	46957	1	.	A	bias_e_value=47991.1	bias_p_value=0.989467	consensus_score=131.6	fisher_strand_p_value=1	frequency=1	gene_name=bor/lambdap78	gene_position=intergenic (-205/+85)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	ks_quality_p_value=0.858413	locus_tag=lambdap77/lambdap78	major_base=A	major_cov=21/24	major_frequency=8.036e-01	minor_base=.	minor_cov=5/6	new_cov=21/24	polymorphism_frequency=8.036e-01	polymorphism_score=32.2	prediction=consensus	ref_cov=5/6	snp_type=intergenic	total_cov=26/30
RA	43	.	NC_001416.1	46985	0	C	T	consensus_score=250.2	frequency=1	gene_name=bor/lambdap78	gene_position=intergenic (-233/+57)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	major_base=T	major_cov=47/35	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=47/35	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=47/35
RA	44	.	NC_001416.1	46992	0	C	T	bias_e_value=29478.8	bias_p_value=0.607785	consensus_score=167.3	fisher_strand_p_value=0.500565	frequency=1	gene_name=bor/lambdap78	gene_position=intergenic (-240/+50)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	ks_quality_p_value=0.515783	locus_tag=lambdap77/lambdap78	major_base=T	major_cov=32/26	major_frequency=9.667e-01	minor_base=C	minor_cov=2/0	new_cov=32/26	polymorphism_frequency=9.667e-01	polymorphism_score=-2.8	prediction=consensus	ref_cov=2/0	snp_type=intergenic	total_cov=34/26
RA	45	.	NC_001416.1	47004	0	G	A	consensus_score=159.6	frequency=1	gene_name=bor/lambdap78	gene_position=intergenic (-252/+38)	gene_product=Bor protein precursor/putative envelope protein	gene_strand=</<	locus_tag=lambdap77/lambdap78	major_base=A	major_cov=24/33	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=24/33	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=24/33
RA	46	.	NC_001416.1	47129	0	A	G	aa_new_seq=H	aa_position=149	aa_ref_seq=H	codon_new_seq=CAC	codon_number=149	codon_position=3	codon_ref_seq=CAT	consensus_score=195.7	frequency=1	gene_name=lambdap78	gene_position=447	gene_product=putative envelope protein	gene_strand=<	locus_tag=lambdap78	major_base=G	major_cov=36/32	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=36/32	new_seq=G	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=A	snp_type=synonymous	total_cov=36/32	transl_table=11
RA	47	.	NC_001416.1	47143	0	C	T	aa_new_seq=I	aa_position=145	aa_ref_seq=V	bias_e_value=48500.6	bias_p_value=0.999971	codon_new_seq=ATT	codon_number=145	codon_position=1	codon_ref_seq=GTT	consensus_score=192.6	fisher_strand_p_value=1	frequency=1	gene_name=lambdap78	gene_position=433	gene_product=putative envelope protein	gene_strand=<	ks_quality_p_value=0.992337	locus_tag=lambdap78	major_base=T	major_cov=34/30	major_frequency=9.846e-01	minor_base=C	minor_cov=1/0	new_cov=34/30	new_seq=T	polymorphism_frequency=9.846e-01	polymorphism_score=-4.0	prediction=consensus	ref_cov=1/0	ref_seq=C	snp_type=nonsynonymous	total_cov=35/31	transl_table=11
RA	48	.	NC_001416.1	47243	0	G	A	aa_new_seq=N	aa_position=111	aa_ref_seq=N	bias_e_value=48502	bias_p_value=1	codon_new_seq=AAT	codon_number=111	codon_position=3	codon_ref_seq=AAC	consensus_score=195.7	fisher_strand_p_value=1	frequency=1	gene_name=lambdap78	gene_position=333	gene_product=putative envelope protein	gene_strand=<	ks_quality_p_value=0.999534	locus_tag=lambdap78	major_base=A	major_cov=24/41	major_frequency=9.848e-01	minor_base=G	minor_cov=0/1	new_cov=24/41	new_seq=A	polymorphism_frequency=9.848e-01	polymorphism_score=NA	prediction=consensus	ref_cov=0/1	ref_seq=G	snp_type=synonymous	total_cov=24/42	transl_table=11
RA	49	.	NC_001416.1	47315	0	G	A	aa_new_seq=I	aa_position=87	aa_ref_seq=?	bias_e_value=26613.3	bias_p_value=0.548706	codon_new_seq=ATT	codon_number=87	codon_position=3	codon_ref_seq=NTC	consensus_score=287.4	fisher_strand_p_value=0.217105	frequency=1	gene_name=lambdap78	gene_position=261	gene_product=putative envelope protein	gene_strand=<	ks_quality_p_value=1	locus_tag=lambdap78	major_base=A	major_cov=43/51	major_frequency=9.792e-01	minor_base=C	minor_cov=2/0	new_cov=43/51	new_seq=A	polymorphism_frequency=9.792e-01	polymorphism_score=-3.9	prediction=consensus	ref_cov=1/0	ref_seq=G	snp_type=synonymous	total_cov=46/51	transl_table=11
RA	50	.	NC_001416.1	47317	0	N	T	aa_new_seq=I	aa_position=87	aa_ref_seq=?	bias_e_value=48444	bias_p_value=0.998805	codon_new_seq=ATT	codon_number=87	codon_position=1	codon_ref_seq=NTC	consensus_score=309.2	fisher_strand_p_value=1	frequency=1	gene_name=lambdap78	gene_position=259	gene_product=putative envelope protein	gene_strand=<	ks_quality_p_value=0.951516	locus_tag=lambdap78	major_base=T	major_cov=50/51	major_frequency=9.902e-01	minor_base=G	minor_cov=0/1	new_cov=50/51	new_seq=T	polymorphism_frequency=9.902e-01	polymorphism_score=-3.3	prediction=consensus	ref_cov=0/0	ref_seq=N	snp_type=nonsynonymous	total_cov=50/52	transl_table=11
RA	51	.	NC_001416.1	47360	0	G	A	aa_new_seq=N	aa_position=72	aa_ref_seq=N	codon_new_seq=AAT	codon_number=72	codon_position=3	codon_ref_seq=AAC	consensus_score=195.7	frequency=1	gene_name=lambdap78	gene_position=216	gene_product=putative envelope protein	gene_strand=<	locus_tag=lambdap78	major_base=A	major_cov=23/41	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=23/41	new_seq=A	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=G	snp_type=synonymous	total_cov=23/41	transl_table=11
RA	52	.	NC_001416.1	47398	0	C	T	aa_new_seq=N	aa_position=60	aa_ref_seq=D	bias_e_value=35613.5	bias_p_value=0.734269	codon_new_seq=AAC	codon_number=60	codon_position=1	codon_ref_seq=GAC	consensus_score=225.0	fisher_strand_p_value=0.434211	frequency=1	gene_name=lambdap78	gene_position=178	gene_product=putative envelope protein	gene_strand=<	ks_quality_p_value=0.843813	locus_tag=lambdap78	major_base=T	major_cov=32/43	major_frequency=9.868e-01	minor_base=C	minor_cov=1/0	new_cov=32/43	new_seq=T	polymorphism_frequency=9.868e-01	polymorphism_score=-3.6	prediction=consensus	ref_cov=1/0	ref_seq=C	snp_type=nonsynonymous	total_cov=33/43	transl_table=11
RA	53	.	NC_001416.1	47509	0	T	C	aa_new_seq=A	aa_position=23	aa_ref_seq=T	codon_new_seq=GCG	codon_number=23	codon_position=1	codon_ref_seq=ACG	consensus_score=161.8	frequency=1	gene_name=lambdap78	gene_position=67	gene_product=putative envelope protein	gene_strand=<	locus_tag=lambdap78	major_base=C	major_cov=34/24	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=34/24	new_seq=C	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=T	snp_type=nonsynonymous	total_cov=34/24	transl_table=11
RA	54	.	NC_001416.1	47529	0	C	T	aa_new_seq=K	aa_position=16	aa_ref_seq=R	bias_e_value=48502	bias_p_value=1	codon_new_seq=AAG	codon_number=16	codon_position=2	codon_ref_seq=AGG	consensus_score=248.3	fisher_strand_p_value=1	frequency=1	gene_name=lambdap78	gene_position=47	gene_product=putative envelope protein	gene_strand=<	ks_quality_p_value=1	locus_tag=lambdap78	major_base=T	major_cov=40/41	major_frequency=9.878e-01	minor_base=G	minor_cov=0/1	new_cov=40/41	new_seq=T	polymorphism_frequency=9.878e-01	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=C	snp_type=nonsynonymous	total_cov=40/42	transl_table=11
RA	55	.	NC_001416.1	47575	0	C	A	aa_new_seq=M	aa_position=1	aa_ref_seq=M	bias_e_value=38550.3	bias_p_value=0.794819	codon_new_seq=TTG	codon_number=1	codon_position=1	codon_ref_seq=GTG	consensus_score=222.6	fisher_strand_p_value=0.432432	frequency=1	gene_name=lambdap78	gene_position=1	gene_product=putative envelope protein	gene_strand=<	ks_quality_p_value=0.99963	locus_tag=lambdap78	major_base=A	major_cov=31/42	major_frequency=9.865e-01	minor_base=C	minor_cov=1/0	new_cov=31/42	new_seq=A	polymorphism_frequency=9.865e-01	polymorphism_score=NA	prediction=consensus	ref_cov=1/0	ref_seq=C	snp_type=synonymous	total_cov=32/42	transl_table=11
RA	56	.	NC_001416.1	47669	0	T	C	consensus_score=244.4	frequency=1	gene_name=lambdap78/lambdap79	gene_position=intergenic (-94/-69)	gene_product=putative envelope protein/hypothetical protein	gene_strand=</>	locus_tag=lambdap78/lambdap79	major_base=C	major_cov=43/43	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=43/43	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=43/43
RA	57	.	NC_001416.1	47878	0	A	G	aa_new_seq=R	aa_position=47	aa_ref_seq=R	codon_new_seq=AGG	codon_number=47	codon_position=3	codon_ref_seq=AGA	consensus_score=225.7	frequency=1	gene_name=lambdap79	gene_position=141	gene_product=hypothetical protein	gene_strand=>	locus_tag=lambdap79	major_base=G	major_cov=33/49	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=33/49	new_seq=G	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	ref_seq=A	snp_type=synonymous	total_cov=33/49	transl_table=11
RA	58	.	NC_001416.1	47973	0	T	C	consensus_score=229.5	frequency=1	gene_name=lambdap79/–	gene_position=intergenic (+29/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	major_base=C	major_cov=38/42	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=38/42	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=38/42
RA	59	.	NC_001416.1	47977	0	G	A	consensus_score=182.2	frequency=1	gene_name=lambdap79/–	gene_position=intergenic (+33/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	major_base=A	major_cov=31/31	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=31/31	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=31/31
RA	60	.	NC_001416.1	47978	0	T	C	consensus_score=176.3	frequency=1	gene_name=lambdap79/–	gene_position=intergenic (+34/–)	gene_product=hypothetical protein/–	gene_strand=>/–	locus_tag=lambdap79/–	major_base=C	major_cov=31/31	major_frequency=1.000e+00	minor_base=N	minor_cov=0/0	new_cov=31/31	polymorphism_frequency=1.000e+00	polymorphism_score=NA	prediction=consensus	ref_cov=0/0	snp_type=intergenic	total_cov=31/31
RA	61	.	NC_001416.1	48160	0	T	C	bias_e_value=42087.4	bias_p_value=0.867745	consensus_score=145.2	fisher_strand_p_value=0.577923	frequency=1	gene_name=lambdap79/–	gene_position=intergenic (+216/–)	gene_product=hypothetical protein/–	gene_strand=>/–	ks_quality_p_value=0.920521	locus_tag=lambdap79/–	major_base=C	major_cov=34/35	major_frequency=8.214e-01	minor_base=T	minor_cov=6/9	new_cov=34/35	polymorphism_frequency=8.214e-01	polymorphism_score=26.8	prediction=consensus	ref_cov=6/9	snp_type=intergenic	total_cov=40/44
MC	62	.	NC_001416.1	1	2	0	0	gene_name=–/nu1	gene_position=intergenic (–/-189)	gene_product=–/DNA packaging protein	gene_strand=–/>	left_inside_cov=0	left_outside_cov=NA	locus_tag=–/lambdap01	right_inside_cov=0	right_outside_cov=157
MC	63	.	NC_001416.1	21738	27733	0	0	gene_name=[orf-314]–ea59	gene_product=[orf-314],orf-194,ea47,ea31,ea59	left_inside_cov=0	left_outside_cov=100	locus_tag=[lambdap28]–[lambdap82]	right_inside_cov=0	right_outside_cov=100
MC	64	.	NC_001416.1	48468	48502	0	0	gene_name=lambdap79/–	gene_position=intergenic (+524/–)	gene_product=hypothetical protein/–	gene_strand=>/–	left_inside_cov=22	left_outside_cov=28	locus_tag=lambdap79/–	right_inside_cov=0	right_outside_cov=NA
JC	65	.	NC_001416.1	21737	-1	NC_001416.1	27734	1	0	alignment_overlap=5	coverage_minus=29	coverage_plus=32	flanking_left=35	flanking_right=35	frequency=1	junction_possible_overlap_registers=29	key=NC_001416.1__21737__-1__NC_001416.1__27729__1__5____35__35__0__0	max_left=29	max_left_minus=27	max_left_plus=29	max_min_left=13	max_min_left_minus=13	max_min_left_plus=11	max_min_right=15	max_min_right_minus=15	max_min_right_plus=15	max_pos_hash_score=58	max_right=29	max_right_minus=29	max_right_plus=28	neg_log10_pos_hash_p_value=0.2	new_junction_coverage=0.81	new_junction_read_count=78	polymorphism_frequency=1.000e+00	pos_hash_score=35	prediction=consensus	side_1_annotate_key=gene	side_1_continuation=0	side_1_coverage=0.00	side_1_gene_name=orf-314	side_1_gene_position=coding (709/945 nt)	side_1_gene_product=Tail fiber	side_1_gene_strand=>	side_1_locus_tag=lambdap28	side_1_overlap=5	side_1_possible_overlap_registers=34	side_1_read_count=0	side_1_redundant=0	side_2_annotate_key=gene	side_2_continuation=0	side_2_coverage=0.00	side_2_gene_name=ea59/int	side_2_gene_position=intergenic (-761/+78)	side_2_gene_product=ea59/integration protein	side_2_gene_strand=</<	side_2_locus_tag=lambdap82/lambdap33	side_2_overlap=0	side_2_possible_overlap_registers=29	side_2_read_count=0	side_2_redundant=0	total_non_overlap_reads=61
UN	66	.	NC_001416.1	1	8
UN	67	.	NC_001416.1	21738	27733
UN	68	.	NC_001416.1	48486	48486
UN	69	.	NC_001416.1	48490	48490
UN	70	.	NC_001416.1	48492	48492
UN	71	.	NC_001416.1	48494	48502
