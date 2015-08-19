Name

    MESA_ycbcr_texture

Name Strings

    GL_MESA_ycbcr_texture

Contact

    Brian Paul, Tungsten Graphics, Inc. (brian 'at' tungstengraphics.com)
    Keith Whitwell, Tungsten Graphics, Inc.  (keith 'at' tungstengraphics.com)

Status

    Shipping (Mesa 4.0.4 and later)

Version

    1.0

Number

    TBD

Dependencies

    OpenGL 1.0 or later is required
    This extensions is written against the OpenGL 1.4 Specification.
    NV_texture_rectangle effects the definition of this extension.

Overview

    This extension supports texture images in the YCbCr format.  There is
    no support for converting YCbCr images to RGB or vice versa.  The
    intention is for YCbCr image data to be directly sent to the renderer
    without any pixel transfer operations.  Only 2D texture images are
    supported (not glDrawPixels, glReadPixels, etc).

    A YCbCr pixel (texel) is a 16-bit unsigned short with two components.
    The first component is luminance (Y).  For pixels in even-numbered
    image columns, the second component is Cb.  For pixels in odd-numbered
    image columns, the second component is Cr.  If one were to convert the
    data to RGB one would need to examine two pixels from columns N and N+1
    (where N is even) to deduce the RGB color.

IP Status

    None

Issues

    None

New Procedures and Functions

    None

New Tokens

    Accepted by the <internalFormat> and <format> parameters of
    TexImage2D and TexSubImage2D:

        GL_YCBCR_MESA                   0x8757

    Accepted by the <type> parameter of TexImage2D and TexSubImage2D:

        GL_UNSIGNED_SHORT_8_8_MESA      0x85BA /* same as Apple's */
        GL_UNSIGNED_SHORT_8_8_REV_MESA  0x85BB /* same as Apple's */

Additions to Chapter 2 of the OpenGL 1.4 Specification (OpenGL Operation)

    None

Additions to Chapter 3 of the OpenGL 1.4 Specification (Rasterization)

    In section 3.6.4, Rasterization of Pixel Rectangles, on page 102,
    add the following to Table 3.8 (Packed pixel formats):
    
    type Parameter                GL Data   Number of        Matching
     Token Name                    Type     Components     Pixel Formats
    --------------                -------   ----------     -------------
    UNSIGNED_SHORT_8_8_MESA       ushort         3         YCBCR_422_MESA
    UNSIGNED_SHORT_8_8_REV_MESA   ushort         3         YCBCR_422_MESA


    In section 3.6.4, Rasterization of Pixel Rectangles, on page 102,
    add the following to Table 3.10 (UNSIGNED_SHORT formats):

    UNSIGNED_SHORT_8_8_MESA:

      15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
    +-------------------------------+-------------------------------+
    |              1st              |              2nd              |
    +-------------------------------+-------------------------------+
                        
    UNSIGNED_SHORT_8_8_REV_MESA:

      15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
    +-------------------------------+-------------------------------+
    |              2nd              |              1st              |
    +-------------------------------+-------------------------------+


    In section 3.6.4, Rasterization of Pixel Rectangles, on page 102,
    add the following to Table 3.12 (Packed pixel fiedl assignments):

                       First       Second     Third      Fourth
    Format             Element     Element    Element    Element
    ------             -------     -------    -------    -------
    YCBCR_422_MESA     luminance   chroma


    In section 3.8.1, Texture Image Specification, on page 125, add
    another item to the list of TexImage2D and TexImage3D equivalence
    exceptions:

    * The value of internalformat and format may be YCBCR_MESA to
      indicate that the image data is in YCbCr format.  type must
      be either UNSIGNED_SHORT_8_8_MESA or UNSIGNED_SHORT_8_8_REV_MESA
      as seen in tables 3.8 and 3.10.  Table 3.12 describes the mapping
      between Y and Cb/Cr to the components.
      If NV_texture_rectangle is supported target may also be
      TEXTURE_RECTANGLE_NV or PROXY_TEXTURE_RECTANGLE_NV.
      All pixel transfer operations are bypassed.  The texture is stored as
      YCbCr, not RGB.  Queries of the texture's red, green and blue component
      sizes will return zero.


    In section 3.8.1, Texture Image Specification, on page 126, add
    another item to the list of TexImage1D and TexImage2D equivalence
    exceptions:

    * The value of internalformat and format can not be YCBCR_MESA.


    In section 3.8.2, Alternate Texture Image Specification Commands, on
    page 129, insert this paragraph after the first full paragraph on the
    page:

         "If the internal storage format of the image being updated by
    TexSubImage2D is YCBCR_MESA then format must be YCBCR_MESA.
    The error INVALID_OPERATION will be generated otherwise."


Additions to Chapter 4 of the OpenGL 1.4 Specification (Per-Fragment
Operations and the Frame Buffer)

    None

Additions to Chapter 5 of the OpenGL 1.4 Specification (Special Functions)

    None

Additions to Chapter 6 of the OpenGL 1.4 Specification (State and
State Requests)

    None

Additions to Appendix A of the OpenGL 1.4 Specification (Invariance)

    None

Additions to the AGL/GLX/WGL Specifications

    None

GLX Protocol

    None

Errors

    INVALID_ENUM is generated by TexImage2D if <internalFormat> is
    MESA_YCBCR but <format> is not MESA_YCBCR.

    INVALID_ENUM is generated by TexImage2D if <format> is MESA_YCBCR but
    <internalFormat> is not MESA_YCBCR.

    INVALID_VALUE is generated by TexImage2D if <format> is MESA_YCBCR and
    <internalFormat> is MESA_YCBCR and <border> is not zero.

    INVALID_OPERATION is generated by TexSubImage2D if the internal image
    format is YCBCR_MESA and format is not YCBCR_MESA.

    INVALID_OPERATION is generated by CopyTexSubImage2D if the internal
    image is YCBCR_MESA.
    
New State

    Edit table 6.16 on page 231: change the type of TEXTURE_INTERNAL_FORMAT
    from n x Z42 to n x Z43 to indicate that internal format may also be
    YCBCR_MESA.

Revision History

    20 September 2002 - Initial draft